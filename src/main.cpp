#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include <dpp/dpp.h>
#include "utfconvs.hpp"
#include "wys_lib_cpp.hpp"
#include "word_check.hpp"
#include "command_parser.hpp"
#include "math.hpp"

std::string resolve_const(const std::string &const_name) {
	auto it = constants.find(const_name);
	return it == constants.end() ? "<undefined>" : it->second;
}

std::string db17_wrapper(const std::string &data, unsigned long long n) {
	return utf8::from(dontbother17_decrypt(utf32::from(data), n));
}
std::string db17e_wrapper(const std::string &data, unsigned long long n) {
	return utf8::from(dontbother17_encrypt(utf32::from(data), n));
}
std::string decrypt_wrapper(const std::string &data, const std::string &key) {
	return utf8::from(humanscantsolvethis_decrypt(utf32::from(data), key));
}
std::string encrypt_wrapper(const std::string &data, const std::string &key) {
	return utf8::from(humanscantsolvethis_encrypt(utf32::from(data), key));
}
std::string l5decrypt_wrapper(const std::string &data, const std::vector<int> &key) {
	return utf8::from(intelligencecheck_decrypt(utf32::from(data), key));
}
std::string l5encrypt_wrapper(const std::string &data, const std::vector<int> &key) {
	return utf8::from(intelligencecheck_encrypt(utf32::from(data), key));
}
std::string mask_wrapper(const std::string &data, const std::string &chars) {
	return utf8::from(mask_data(utf32::from(data), utf32::from(chars)));
}
void reply(const dpp::message_create_t &event, const std::string &msg) {
	std::cout << "[command]: " << event.msg.content << " (by " << event.msg.author.username << ")" << std::endl;
	std::cout << "\t[reply]: " << msg << std::endl;
	event.reply(dpp::message(msg), true);
}
void reply(const dpp::message_create_t &event, const dpp::snowflake &snowflake, const dpp::embed &emb) {
	std::cout << "[command]: " << event.msg.content << " (by " << event.msg.author.username << ")" << std::endl;
	std::cout << "\t[reply]: embed{}" << std::endl;
	event.reply(dpp::message(snowflake, emb).set_reference(event.msg.id), true);
}
template<typename F>
void dontbother(const std::string &rest, command_parser &cmd, const dpp::message_create_t &event, F func, const char *msg) {
	unsigned long long n;
	if (rest.size() > 0) {
		if (std::all_of(rest.begin(), rest.end(), [](char c) { return std::isdigit(c); })) {
			if (rest.size() > 0)
			n = std::stoull(rest);
		} else {
			reply(event, msg);
			return;
		}
	} else {
		if (!cmd.try_next(n)) {
			reply(event, "N must be a number");
			return;
		}
	}
	std::string data = cmd.next_resolved();
	if (data.empty()) {
		reply(event, "empty data - result is empty too then :)");
		return;
	}
	reply(event, "```\n"+func(data, n)+"\n```");
}
template<typename F>
void decrypt_encrypt(command_parser &cmd, const dpp::message_create_t &event, F func) {
	std::string key = cmd.next_resolved();
	if (key.empty()) {
		reply(event, "key can't be empty");
		return;
	} else if (!std::all_of(key.begin(), key.end(), [](char c) { return c >= 'A' && c <= '}'; })) {
		reply(event, "invalid key (`" + key + "`)");
		return;
	}
	std::string data = cmd.next_resolved();
	if (data.empty()) {
		reply(event, "empty data - result is empty too then :)");
		return;
	}
	reply(event, "```\n" + func(data, key) + "\n```");
}

template<typename F>
void l5decrypt_l5encrypt(command_parser &cmd, const dpp::message_create_t &event, F func) {
	std::string key = cmd.next_resolved();
	key.erase(std::remove_if(key.begin(), key.end(), [](char c) { return std::isspace(c); }), key.end());
	if (key.empty()) {
		reply(event, "key can't be empty");
		return;
	} else if (!std::all_of(key.begin(), key.end(), [](char c) { return (c >= '0' && c <= '9') || c == ',' || c == '-'; })) {
		reply(event, "invalid key (`" + key + "`)");
		return;
	}
	std::vector<int> k;
	int buff = 0;
	for (auto it = key.begin(); it != key.end(); it++) {
		switch (*it) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': buff *= 10; buff += *it - '0'; break;
		case ',': k.push_back(buff); buff = 0; break;
		case '-': 
			it++;
			if (it == key.end() || *it < '0' || *it > '9') {
				reply(event, "invalid key (`" + key + "`)");
				return;
			}
			buff = '0' - *it;
			break;
		}
	}
	k.push_back(buff);
	for (int i : k) {
		std::cout << "_" << i;
	}
	std::cout << std::endl;
	std::string data = cmd.next_resolved();
	if (data.empty()) {
		reply(event, "empty data - result is empty too then :)");
		return;
	}
	reply(event, "```\n" + func(data, k) + "\n```");
}
template<typename F>
void datafunc(command_parser &cmd, const dpp::message_create_t &event, F func) {
	std::string data = cmd.next_resolved();
	reply(event, "```\n" + func(data) + "\n```");
}
template<typename F>
void strdatafunc(command_parser &cmd, const dpp::message_create_t &event, F func) {
	std::string str = cmd.next_resolved();
	if (str.empty()) {
		reply(event, "str can't be empty");
		return;
	}std::string data = cmd.next_resolved();
	reply(event, "```\n" + func(data, str) + "\n```");
}
std::mt19937_64 random_gen;
template<typename T, typename GT>
void rng(command_parser &cmd, const dpp::message_create_t &event, const char *msgbonus) {
	T a, b;
	if (!cmd.try_next(a)) { reply(event, std::string("enter minimum") + msgbonus); return; }
	if (!cmd.try_next(b)) { reply(event, std::string("enter maximum") + msgbonus); return; }
	if (b < a) { std::swap(a, b); }
	T res = GT(a, b)(random_gen);
	reply(event, "random number between " + std::to_string(a) + " and " + std::to_string(b) + " (both inclusive) is " + std::to_string(res));
}

trie_node trie;

int main() {
	std::random_device rd;
	random_gen.seed(rd());
	std::string token;
	{
		std::ifstream f("./apikey");
		std::getline(f, token);
	}
	trie.load_file("./word_list_1k.txt", 0);
	dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);
	bot.on_log(dpp::utility::cout_logger());
	bot.on_message_create([](const dpp::message_create_t &event) {
		if (!event.msg.author.is_bot() && event.msg.content.starts_with("!") || event.msg.content.starts_with("d!")) {
			command_parser cmd(event.msg.content);
			std::string cmdname = cmd.word();
			std::cerr << "[command]: " << event.msg.content << " (by " << event.msg.author.username << ")" << std::endl;
			if (cmdname == "help" || cmdname == "man") {
				std::string cmd2 = cmd.next();
				dpp::embed help_embed = dpp::embed().set_color(dpp::colors::dark_goldenrod);
				if (cmd2.empty()) {
					help_embed.set_title("DecryptBot help")
						.set_description("use with `d!command` or `!command`, aliases are in parentheses")
						.add_field(
							"Misc",
							"help (man), rng, frng, math, imath"
						).add_field(
							"Decrypt/Encrypt",
							"dontbother (db), dontbother_encrypt (dbe), decrypt (d), encrypt (e), l5decrypt (d5), l5encrypt (e5)"
						).add_field(
							"Utility",
							"resolve, mask, score, frequency (freq), find_key (rev)"
						).add_field(
							"how to use those commands?",
							"use !help commands to get more info on how commands work, !help <command> to get more info about specific command"
						);
				} else if (cmd2 == "commands" || cmd2 == "cmds") {
					help_embed.set_title("DecryptBot help")
						.set_description("format: `d!command [args...]`")
						.add_field(
							"Argument tokens",
							"word ([a-zA-Z0-9_$\\-]+)\ninline code (\\`[^\\`]*\\`) - can be used to group words or use non-word characters\n"
							"block code (\\`\\`\\`.*\\`\\`\\`)\nother non-whitespace characters are taken 1 by 1"
						).add_field(
							"Arguments",
							"each argument consists of __**one**__ argument token, but there are some special cases:\n"
							"typed arguments - contents are parsed into some other type, like int\n"
							"resolved arguments - when the contents start with `$`, it gets replaced by constant value for that (use `!help constants` for list)"
						);
				} else if (cmd2 == "constants") {
					help_embed.set_title("DecryptBot constants")
						.set_description("`L1D` - L1 data\n`L2D` - L2 data\n...\n`L1T` - L1 text\n...\n`L2K` - L2 key\n...");
				} else if (cmd2 == "help" || cmd2 == "man") {
					help_embed.set_title("DecryptBot help for `d!help`")
						.set_description("`d!help [commands|constants]` or `d!help <command>`")
						.add_field(
							"Shows help",
							"`d!help` - shows all commands and a bit more info\n"
							"`d!help commands` (`!help cmds`) - shows how to use commands\n"
							"`d!help constants` - shows constant list\n"
							"`d!help <command>` - shows help for the command\n"
						).add_field(
							"Aliases",
							"help, man"
						);
				} else if (cmd2 == "debug") {
					help_embed.set_title("DecryptBot help for `d!debug`")
						.set_description("I'm too lazy to document a commant that's not supposed to be used by others :)");
				} else if (cmd2 == "dontbother" || cmd2 == "db") {
					help_embed.set_title("DecryptBot help for `d!dontbother`")
						.set_description("`d!dontbother <N:typed - i64> <data:resolved>` or `d!dontbother<N:typed - i64> <data:resolved>`")
						.add_field(
							"Decrypts `data` using the _dontbother_ algorithm and N",
							"..."
						).add_field(
							"Aliases",
							"dontbother, db"
						);
				} else if (cmd2 == "dontbother_encrypt" || cmd2 == "dbe") {
					help_embed.set_title("DecryptBot help for `d!dontbother_encrypt`")
						.set_description("`d!dontbother_encrypt <N:typed - i64> <data:resolved>` or `d!dontbother_encrypt<N:typed - i64> <data:resolved>`")
						.add_field(
							"Encrypts `data` using the _dontbother_ algorithm and N",
							"..."
						).add_field(
							"Aliases",
							"dontbother_encrypt, dbe"
						);
				} else if (cmd2 == "decrypt" || cmd2 == "d") {
					help_embed.set_title("DecryptBot help for `d!decrypt`")
						.set_description("`d!decrypt <key:resolved> <data:resolved>`")
						.add_field(
							"Decrypts `data` using the _humanscantsolvethis_ algorithm with key `key`",
							"..."
						).add_field(
							"Aliases",
							"decrypt, d"
						);
				} else if (cmd2 == "encrypt" || cmd2 == "e") {
					help_embed.set_title("DecryptBot help for `d!encrypt`")
						.set_description("`d!encrypt <key:resolved> <data:resolved>`")
						.add_field(
							"Encrypts `data` using the _humanscantsolvethis_ algorithm with key `key`",
							"..."
						).add_field(
							"Aliases",
							"encrypt, e"
						);
				} else if (cmd2 == "l5decrypt" || cmd2 == "d5") {
					help_embed.set_title("DecryptBot help for `d!l5decrypt`")
						.set_description("`d!l5decrypt <key:resolved, typed> <data:resolved>`")
						.add_field(
							"Decrypts `data` using the _intelligencecheck_ algorithm with key `key`",
							"key is a comma separated list of numbers, like `0,12,-3,3,5`"
						).add_field(
							"Aliases",
							"l5decrypt, d5"
						);
				} else if (cmd2 == "l5encrypt" || cmd2 == "e5") {
					help_embed.set_title("DecryptBot help for `d!l5encrypt`")
						.set_description("`d!encrypt <key:resolved, typed> <data:resolved>`")
						.add_field(
							"Encrypts `data` using the _intelligencecheck_ algorithm with key `key`",
							"key is a comma separated list of numbers, like `0,12,-3,3,5`"
						).add_field(
							"Aliases",
							"l5encrypt, e5"
						);
				} else if (cmd2 == "resolve") {
					help_embed.set_title("DecryptBot help for `d!resolve`")
						.set_description("`d!resolve <constant>`")
						.add_field(
							"Gets value of `constant`",
							"use it without the `$` prefix - it isn't resolved argument"
						);
				} else if (cmd2 == "mask") {
					help_embed.set_title("DecryptBot help for `d!mask`")
						.set_description("`d!mask <chars:resolved> <data:resolved>`")
						.add_field(
							"Masks out all characters not present in `chars` from data",
							"masked out characters are replaced with (`.`)"
						);
				} else if (cmd2 == "score") {
					help_embed.set_title("DecryptBot help for `d!score`")
						.set_description("`d!score <data:resolved>`")
						.add_field(
							"Scores the data",
							"I know, it's pretty useless :D, also the results seem a bit weird :/"
						);
				} else if (cmd2 == "frequency" || cmd2 == "freq") {
					help_embed.set_title("DecryptBot help for `d!frequency`")
						.set_description("`d!frequency <data:resolved>`")
						.add_field(
							"Shows the character frequency of `data`",
							"It's sorted from most frequent characters"
						).add_field(
							"Aliases",
							"frequency, freq"
						);
				} else if (cmd2 == "rng") {
					help_embed.set_title("DecryptBot help for `d!rng`")
						.set_description("`d!rng <a:typed i64> <b:typed i64>`")
						.add_field(
							"Generates random number between a and b",
							"both extremes are inclusive"
						);
				} else if (cmd2 == "frng") {
					help_embed.set_title("DecryptBot help for `d!frng`")
						.set_description("`d!frng <a:typed f64> <b:typed f64>`")
						.add_field(
							"Generates random number between a and b",
							"both extremes are inclusive, generates real numbers, not just integers"
						);
				} else if (cmd2 == "math") {
					help_embed.set_title("DecryptBot help for `d!math`")
						.set_description("`d!math <expression:rest of the message :)>`")
						.add_field(
							"Evaluates an expression",
							"uses custom expression parser - uses only `double`s and supports just these operators: `+-*/^%()`\n"
							"`^` is power and `%` is modulo"
						);
				} else if (cmd2 == "find_key" || cmd2 == "rev") {
					help_embed.set_title("DecryptBot help for `d!find_key`")
						.set_description("`d!find_key <result:resolved> <data:resolved>`")
						.add_field(
							"Finds key which would create `result` at the beggining",
							"(max 15 characters long `result`)"
						).add_field(
							"Aliases",
							"find_key, rev"
						);
				} else {
					help_embed.set_title("that command doesn't have help for itself or doesn't exist");
				}
				reply(event, event.msg.channel_id, help_embed);
			} else if (cmdname == "debug") {
				std::string subcmd = cmd.next();
				if (subcmd == "reply") {
					reply(event, "debug reply");
				} else if (subcmd == "echo") {
					reply(event, "```\n" + cmd.next() + "\n```");
				}
			} else if (cmdname.starts_with("dbe")) {
				dontbother(cmdname.substr(3), cmd, event, db17e_wrapper, "use as d!dbeN DATA or d!dbe N DATA");
			} else if (cmdname.starts_with("dontbother_encrypt")) {
				dontbother(cmdname.substr(18), cmd, event, db17e_wrapper, "use as d!dontbother_encryptN DATA or d!dontbother_encrypt N DATA");
			} else if (cmdname.starts_with("db")) {
				dontbother(cmdname.substr(2), cmd, event, db17_wrapper, "use as d!dbN DATA or d!db N DATA");
			} else if (cmdname.starts_with("dontbother")) {
				dontbother(cmdname.substr(10), cmd, event, db17_wrapper, "use as d!dontbotherN DATA or d!dontbother N DATA");
			} else if (cmdname == "decrypt" || cmdname == "d") {
				decrypt_encrypt(cmd, event, decrypt_wrapper);
			} else if (cmdname == "encrypt" || cmdname == "e") {
				decrypt_encrypt(cmd, event, encrypt_wrapper);
			} else if (cmdname == "l5decrypt" || cmdname == "d5") {
				l5decrypt_l5encrypt(cmd, event, l5decrypt_wrapper);
			} else if (cmdname == "l5encrypt" || cmdname == "e5") {
				l5decrypt_l5encrypt(cmd, event, l5encrypt_wrapper);
			} else if (cmdname == "resolve") {
				auto it = constants.find(cmd.next());
				if (it == constants.end())
					reply(event, "<undefined constant>");
				else
					reply(event, it->second);
			} else if (cmdname == "mask") {
				strdatafunc(cmd, event, mask_wrapper);
			} else if (cmdname == "score") {
				datafunc(cmd, event, [](const std::string &data) { return std::to_string(message_likeliness(data, trie)); });
			} else if (cmdname == "frequency" || cmdname == "freq") {
				datafunc(cmd, event, frequency);
			} else if (cmdname == "rng") {
				rng<long long int, std::uniform_int_distribution<long long int>>(cmd, event, " (integer)");
			} else if (cmdname == "frng") {
				rng<double, std::uniform_real_distribution<double>>(cmd, event, " (real number)");
			} else if (cmdname == "math") {
				reply(event, calc(cmd.rest()));
			} else if (cmdname == "imath") {
				reply(event, "this command is unfinished :(");
			} else if (cmdname == "find_key" || cmdname == "rev") {
				std::string result = cmd.next_resolved();
				if (result.empty()) {
					reply(event, "wanted result is empty!");
					return;
				}
				std::string data = cmd.next_resolved();
				if (data.empty()) {
					reply(event, "empty data!");
					return;
				} else if (data.size() < result.size()) {
					reply(event, "too short data!");
					return;
				}
				std::ostringstream ss;
				ss << "```\n";
				unsigned int count = 0;
				for (const auto &k : humanscantsolvethis_keys_from_result(data, result)) {
					ss << k << " ";
					if (++count > 1900 / (result.size() + 1)) {
						ss << " + more";
						break;
					}
				}
				if (count == 0) {
					ss << "<none>";
				}
				ss << "\n```";
				reply(event, ss.str());
			}
		}
	});
	bot.start(dpp::st_wait);
	return 0;
}
