#pragma once

#include <iostream>
#include <map>
#include "Node.h"

namespace S1 {
	typedef std::variant<int, float, double, long, bool> POD;

	std::ostream& operator<<(std::ostream& os, const POD& num);

	typedef std::map<std::string, POD> SYMBOL_TABLE;

	std::ostream& operator<<(std::ostream& os, const std::map<std::string, S1::POD> table);

	POD operator+(const POD& left, const POD& right);
	POD operator-(const POD& left, const POD& right);
	POD operator*(const POD& left, const POD& right);
	POD operator/(const POD& left, const POD& right);

	struct Visitor {
		SYMBOL_TABLE GLOBAL_SCOPE = {};

		void Error(const char* text) { std::cout << "[VISITOR ERROR]: " << text << std::endl; }
		void Info(const char* text) { std::cout << "[VISITOR INFO]: " << text << std::endl; }

		POD operator()(const int& visitee) { return (POD)visitee; }
		POD operator()(const bool& visitee) { return (POD)visitee; }
		POD operator()(const long& visitee) { return (POD)visitee; }
		POD operator()(const float& visitee) { return (POD)visitee; }
		POD operator()(const double& visitee) { return (POD)visitee; }

		POD operator()(const UNARYOP& visitee);
		POD operator()(const BINOP& visitee);

		POD operator()(const BINOP_ADD& visitee);
		POD operator()(const BINOP_MIN& visitee);
		POD operator()(const BINOP_MUL& visitee);
		POD operator()(const BINOP_DIV& visitee);

		POD operator()(const UNARYOP_ADD& visitee);
		POD operator()(const UNARYOP_MIN& visitee);

		POD operator()(const COMPOUND& visitee);
		POD operator()(const ASSIGN& visitee);
		POD operator()(const VAR& visitee);

		POD operator()(const NOOP& visitee);
	};
}