#ifndef __COMMAND_PARSER_HPP__
#define __COMMAND_PARSER_HPP__

#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>
#include "wys_lib_cpp.hpp"

inline const std::unordered_map<std::string, std::string> constants = {
	{ "L1D", data1 },
	{ "L2D", data2 },
	{ "L3D", data3 },
	{ "L4D", data4 },
	{ "L5D", data5 },
	{ "L1T", text1 },
	{ "L2T", text2 },
	{ "L3T", text3 },
	{ "L4T", text4 },
	{ "L5T", text5 },
	{ "L2K", key2 },
	{ "L3K", key3 },
	{ "L4K", key4 },
};

class command_parser {
public:
	command_parser(const std::string &contents);
	std::string next();
	std::string word();
	template<typename T>
	inline bool try_next(T &out) {
		std::istringstream ss(next());
		ss >> out;
		return !ss.fail() && ss.eof();
	}
	std::string next_resolved();
	std::string rest();
private:
	std::string cmd;
};

#endif
