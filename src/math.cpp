#include "math.hpp"

#include <cctype>
#include <cmath>
#include <map>
#include <sstream>
#include <stack>

const std::map<char, int> prec = {
	{ '(', 0 },
	{ '+', 10 },
	{ '-', 10 },
	{ '*', 20 },
	{ '/', 20 },
	{ '%', 20 },
	{ '^', 30 },
	{ 'p', 50 },
	{ 'm', 50 },
};
const std::map<char, bool> leftassoc = {
	{ 'p', true },
	{ 'm', true },
	{ '+', true },
	{ '-', true },
	{ '*', true },
	{ '/', true },
	{ '%', true },
	{ '^', false },
	{ '(', false },
};

std::string calc(const std::string &epxression) {
	std::stack<char> ops;
	std::stack<double> vals;
	std::string buff;
	bool unary = true;
	auto do_op = [&vals, &ops]() {
		if (ops.top() == '(') {
			ops.pop();
			return false;
		}
		if (vals.empty()) return true;
		double a = vals.top(); vals.pop();
		if (ops.top() == 'p') {
			ops.pop();
			vals.push(a);
			return false;
		}
		if (ops.top() == 'm') {
			ops.pop();
			vals.push(-a);
			return false;
		}
		if (vals.empty()) return true;
		double b = vals.top(); vals.pop();
		switch (ops.top()) {
		case '+': vals.push(b+a); break;
		case '-': vals.push(b-a); break;
		case '*': vals.push(b*a); break;
		case '/': vals.push(b/a); break;
		case '%': vals.push(std::fmod(b, a)); break;
		case '^': vals.push(static_cast<double>(std::pow(b, a))); break;
		default:
			break;
		}
		ops.pop();
		return false;
	};
	for (auto i = epxression.begin(); i != epxression.end(); i++) {
		if (!buff.empty() && !std::isdigit(*i) && *i != '.') {
			std::istringstream ss(buff);
			double v;
			ss >> v;
			if (ss.fail() || !ss.eof()) {
				return buff + " is not a valid number";
			}
			buff.clear();
			vals.push(v);
		}
		switch (*i) {
		case '+':
		case '-':
			if (unary) {
				ops.push(*i == '+' ? 'p' : 'm');
				break;
			}
			// fall through intentional!
		case '*':
		case '/':
		case '%':
		case '^':
			while (!ops.empty() && (prec.at(*i) < prec.at(ops.top()) || (leftassoc.at(*i) && prec.at(*i) == prec.at(ops.top())))) {
				char opc = ops.top();
				if (do_op())
					return std::string("expected value (`") + opc + "` during `" + *i + "`)";
			}
			ops.push(*i);
			unary = true;
			break;
		case '(':
			if (!unary) {
				while (!ops.empty() && (prec.at(*i) < prec.at(ops.top()) || (leftassoc.at('*') && prec.at('*') == prec.at(ops.top())))) {
					char opc = ops.top();
					if (do_op())
						return std::string("expected value (`") + opc + "` during `implicit *`)";
				}
				ops.push('*');
			}
			ops.push('(');
			unary = true;
			break;
		case ')':
			while (!ops.empty() && ops.top() != '(') {
				char opc = ops.top();
				if (do_op())
					return std::string("expected value (`") + opc + "` during `()`)";
			}
			if (ops.empty()) {
				return "unmatched `)`";
			}
			ops.pop();
			unary = false;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			unary = false;
			buff.push_back(*i);
			break;
		case ' ':
		case '\n':
		case '\t':
		case '`':
			break;
		default:
			if (*i & 0x80) {
				char c = *i;
				unsigned int nbytes = 1;
				while (c & 0x80) {
					c <<= 1;
					nbytes++;
				}
				return std::string("unexpected character (") + epxression.substr(i - epxression.begin(), nbytes) + ")";
			}
			return std::string("unexpected character (") + *i + ")";
		}
	}
	if (!buff.empty()) {
		std::istringstream ss(buff);
		double v;
		ss >> v;
		if (ss.fail() || !ss.eof()) {
			return buff + " is not a valid number";
		}
		buff.clear();
		vals.push(v);
	}
	while (!ops.empty()) {
		char opc = ops.top();
		if (do_op())
			return std::string("expected value (`") + opc + "` during `end`)";
	}
	if (vals.empty()) {
		return "expected value";
	}
	return "```\n" + epxression + " = " + std::to_string(vals.top()) + "\n```";
}
