#ifndef __WORD_CHECK_HPP__
#define __WORD_CHECK_HPP__

/* Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE. */

#include <cctype>
#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class trie_node {
public:
	inline trie_node() : is_terminal(false), children{nullptr} { }

	inline static trie_node load_file(const std::string &file_name, unsigned int word_min_limit) {
		std::ifstream f(file_name);
		if (f.good()) {
			trie_node trie;
			std::string buff;
			while (std::getline(f, buff)) {
				if (buff.size() > word_min_limit && buff[0] != '#')
					trie.add(buff);
			}
			return trie;
		} else {
			std::cerr << "unable to open " << file_name << std::endl;
			return trie_node();
		}
	}

	inline void add(std::string::const_iterator it, std::string::const_iterator end) {
		if (it == end) {
			is_terminal = true;
			return;
		} else if (children[*it - 'a'] == nullptr) {
			children[*it - 'a'] = std::unique_ptr<trie_node>(new trie_node());
		}
		children[*it - 'a']->add(++it, end);
	}
	inline void add(const std::string &str) { add(str.begin(), str.end()); }
	inline bool has(std::string::const_iterator it, std::string::const_iterator end) const {
		if (it == end) {
			return is_terminal;
		} else if (children[*it - 'a'] == nullptr) {
			return false;
		} else {
			return children[*it - 'a']->has(++it, end);
		}
	}
	inline bool has(const std::string &str) const { return has(str.begin(), str.end()); }
	inline bool has(char c) const { return children[c - 'a'] != nullptr; }
	inline bool terminal() const { return is_terminal; }
	inline const trie_node *at(char c) const { return children[c - 'a'].get(); }
	inline const trie_node *operator[](char c) const { return at(c); }
private:
	bool is_terminal;
	std::array<std::unique_ptr<trie_node>, 26> children;
};

struct word_check_data {
	std::string key;
	const trie_node *at_node;
	unsigned int off;

	inline word_check_data(const std::string &key, const trie_node *at_node, unsigned int off) : key(key), at_node(at_node), off(off) { }
};
template<typename F>
inline void check_start(std::string &data, std::string &keybuff, const trie_node *root, const trie_node *node, unsigned int prevskip,
	unsigned int off, unsigned int limit, F callback) {
	keybuff.push_back(static_cast<char>(prevskip + 64));
	if (limit == 0) {
		callback(keybuff);
	} else {
		char removed_char = data[off];
		data.erase(data.begin() + off);
		for (unsigned int skip = 1; skip <= 26; skip++) {
			unsigned int index = (off + skip) % data.size();
			char c = data[index];
			if (c >= 'a' && c <= 'z') {
				if (node != nullptr && node->has(c)) {
					check_start(data, keybuff, root, node->at(c), skip, index, limit - 1, callback);
				}
			} else if (c == ' ') {
				if (node == nullptr || node->terminal()) {
					check_start(data, keybuff, root, root, skip, index, limit - 1, callback);
				}
			} else if (c == ';') {
				if (node != nullptr && node->terminal()) {
					check_start(data, keybuff, root, nullptr, skip, index, limit - 1, callback);
				}
			}
		}
		data.insert(data.begin() + off, removed_char);
	}
	keybuff.pop_back();
}
template<typename F>
inline void check_start(const std::string &data, const trie_node &trie, unsigned int limit, F callback) {
	std::string datacpy(data);
	std::string keybuff;
	keybuff.reserve(limit);
	for (unsigned int skip = 1; skip <= 26; skip++) {
		unsigned int index = skip % datacpy.size();
		char c = data[index];
		if (c >= 'a' && c <= 'z') {
			if (trie.has(c)) {
				check_start(datacpy, keybuff, &trie, trie[c], skip, index, limit - 1, callback);
			}
		}
	}
}
template<typename F>
inline void check_start(const std::string &data, const trie_node &trie, unsigned int limit, F callback, unsigned int skip) {
	std::string datacpy(data);
	std::string keybuff;
	keybuff.reserve(limit);
	unsigned int index = skip % datacpy.size();
	char c = data[index];
	if (c >= 'a' && c <= 'z') {
		if (trie.has(c)) {
			check_start(datacpy, keybuff, &trie, trie[c], skip, index, limit - 1, callback);
		}
	}
}
template<typename F>
inline void check_start(const std::string &data, const trie_node &trie, unsigned int limit, F callback, unsigned int skip1, unsigned int skip2) {
	std::string datacpy(data);
	std::string keybuff;
	keybuff.reserve(limit);
	unsigned int index1 = skip1 % datacpy.size();
	char c1 = data[index1];
	if (c1 >= 'a' && c1 <= 'z') {
		if (trie.has(c1)) {
			const trie_node *node = trie[c1];
			keybuff.push_back(static_cast<char>(skip1 + 64));
			char removed_char = data[index1];
			datacpy.erase(datacpy.begin() + index1);
			unsigned int index2 = (index1 + skip2) % data.size();
			char c = data[index2];
			if (c >= 'a' && c <= 'z') {
				if (node != nullptr && node->has(c)) {
					check_start(datacpy, keybuff, &trie, node->at(c), skip2, index2, limit - 2, callback);
				}
			} else if (c == ' ') {
				if (node != nullptr && node->terminal()) {
					check_start(datacpy, keybuff, &trie, &trie, skip2, index2, limit - 2, callback);
				}
			} else if (c == ';') {
				if (node != nullptr && node->terminal()) {
					check_start(datacpy, keybuff, &trie, nullptr, skip2, index2, limit - 2, callback);
				}
			}
			datacpy.insert(datacpy.begin() + index1, removed_char);
			keybuff.pop_back();
		}
	}
}

constexpr float strike_cost = 0.8f;
constexpr float wrong_word_char_cost = 0.3f;
constexpr float right_word_char_score = 2.f;
constexpr unsigned int combo_requirement = 1;
constexpr inline float combo_score(float combo) { return combo * (combo - 1) * 0.5f; }
template<bool use_upper=false>
float message_likeliness(const std::string &data, const trie_node &trie) {
	std::string buff;
	bool semicolon = false;
	unsigned int chars_word_right = 0;
	unsigned int chars_word_all = 0;
	unsigned int strikes = 0;
	float combo_current = 0;
	float combo = 0;
	for (const char &c : data) {
		if (semicolon) {
			semicolon = false;
			if (c != ' ') {
				strikes++;
			}
		} else {
			if (c == ' ' || c == ';' || c == ':') {
				if (buff.empty()) {
					strikes++;
				} else {
					chars_word_all += buff.size();
					if (trie.has(buff)) {
						chars_word_right += buff.size();
						if (buff.size() == combo_requirement + 1)
							combo_current += 0.1f;
						else if (buff.size() > combo_requirement)
							combo_current += buff.size() * .3f;
					} else if (combo_current >= 1.f) {
						combo += combo_score(combo_current);
						combo_current = 0;
					}
					buff.clear();
				}
				semicolon = c != ' ';
			} else if (use_upper) {
				if (std::isalpha(c)) {
					buff.push_back(std::tolower(c));
				} else {
					if (combo_current >= 1.f) {
						combo += combo_score(combo_current);
						combo_current = 0;
					}
					chars_word_all += buff.size();
					buff.clear();
					strikes++;
				}
			} else {
				if (c >= 'a' && c <= 'z') {
					buff.push_back(c);
				} else {
					if (combo_current >= 1.f) {
						combo += combo_score(combo_current);
						combo_current = 0;
					}
					chars_word_all += buff.size();
					buff.clear();
					strikes++;
				}
			}
		}
	}
	if (combo_current) {
		combo += combo_score(combo_current);
		combo_current = 0;
	}
	return (
			right_word_char_score * static_cast<float>(chars_word_right)
			-wrong_word_char_cost * static_cast<float>(chars_word_all - chars_word_right)
			-strike_cost * static_cast<float>(strikes) +
			combo
		) / static_cast<float>(data.size());
}

#endif
