#ifndef __UTF_CONVS_HPP__
#define __UTF_CONVS_HPP__

#include <algorithm>
#include <stack>
#include <string>

namespace utf8 {
	inline std::string from(const std::u32string &u32s) {
		std::string res;
		for (size_t i = 0; i < u32s.size(); ++i) {
			char32_t c = u32s[i];
			if (c < 0x80) {
				res.push_back(static_cast<char>(c));
			} else {
				std::stack<char> cs;
				size_t len = 1;
				while (c > 0x3f) {
					cs.push((static_cast<char>(c & 0x3f) | 0x80));
					c >>= 6;
					len++;
				}
				if (c >= (0x80 >> len)) {
					cs.push((static_cast<char>(c & 0x3f) | 0x80));
					c >>= 6;
					len++;
				}
				cs.push(~static_cast<char>(0xffu >> static_cast<unsigned char>(len)) | static_cast<char>(c));
				while (!cs.empty()) { res.push_back(cs.top()); cs.pop(); }
			}
		}
		return res;
	}
	inline size_t len(const std::string &s) {
		return std::count_if(s.begin(), s.end(), [](const char &c){ return (c & 0xc0) != 0x80; });
	}
}
namespace utf32 {
	inline std::u32string from(const std::string &u8s) {
		std::u32string res;
		for (size_t i = 0; i < u8s.size(); ++i) {
			char c = u8s[i];
			if (c & 0x80) {
				size_t l = 1;
				while ((c <<= 1) & 0x80) { ++l; }
				char32_t d = static_cast<char32_t>(u8s[i] & 0x3f);
				for (; l > 1; l--) {
					if (i < u8s.size())
						i++;
					d = d << 6 | static_cast<char32_t>(u8s[i] & 0x3f);
				}
				res.push_back(d);
			} else {
				res.push_back(static_cast<char32_t>(c));
			}
		}
		return res;
	}
}

#endif
