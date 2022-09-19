#include "command_parser.hpp"

constexpr bool isword(char c) {
	return std::isalnum(c) || c == '$' || c == '_' || c == '-';
}

command_parser::command_parser(const std::string &contents) : cmd(contents) {
	if (cmd.starts_with("d!")) {
		cmd = cmd.substr(2);
	} else if (cmd.starts_with('!')) {
		cmd = cmd.substr(1);
	}
}
std::string command_parser::next() {
	if (cmd.size() < 1) {
		return "";
	} else if (isword(cmd[0])) {
		return word();
	} else if (std::isspace(cmd[0])) {
		auto it = std::find_if(cmd.begin(), cmd.end(), [](char c) { return !std::isspace(c); });
		cmd.erase(cmd.begin(), it);
		return next();
	} else if (cmd[0] == '`') {
		auto end = cmd.find('`', 1);
		if (end == std::string::npos) {
			std::string out = cmd.substr(1);
			cmd.clear();
			return out;
		} else if (end == 1) {
			if (cmd.size() > 2) {
				if (cmd[2] == '`') {
					end = cmd.find("```", 3);
					if (end == std::string::npos) {
						std::string out = cmd.substr(3);
						cmd.clear();
						return out;
					} else {
						std::string out = cmd.substr(3, end-3);
						cmd.erase(0, end+3);
						if (out.starts_with('\n')) { out.erase(0, 1); }
						if (out.ends_with('\n')) { out.erase(out.size()-1); }
						return out;
					}
				} else {
					cmd.erase(0, 2);
					return "";
				}
			} else {
				cmd.clear();
				return "";
			}
		} else {
			std::string out = cmd.substr(1, end-1);
			cmd.erase(0, end+1);
			return out;
		}
	} else {
		char c = cmd[0];
		cmd.erase(0, 1);
		return std::string(1, c);
	}
}
std::string command_parser::word() {
	auto it = std::find_if(cmd.begin(), cmd.end(), [](char c) { return !isword(c); });
	std::string out = cmd.substr(0, it - cmd.begin());
	cmd.erase(cmd.begin(), it);
	return out;
}
std::string command_parser::rest() {
	std::string out(cmd);
	cmd.clear();
	return out;
}
std::string command_parser::next_resolved() {
	std::string buff = next();
	if (buff.starts_with('$')) {
		auto it = constants.find(buff.substr(1));
		if (it == constants.end())
			return "<undefined constant>";
		return it->second;
	}
	return buff;
}
