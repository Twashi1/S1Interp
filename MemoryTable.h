#pragma once

#include <iostream>
#include <variant>
#include <map>
#include <sstream>

#include "Errors.h"

namespace S1 {
	typedef std::variant<int, float, double, long, bool, std::string> POD;
	std::ostream& operator<<(std::ostream& os, const POD& num);
	S1::POD& operator>>(std::istream& is, S1::POD& pod);
	std::string PODToStr(const POD& num);

	/* POD operators */

	POD operator+(const POD& left, const POD& right);
	POD operator-(const POD& left, const POD& right);
	POD operator*(const POD& left, const POD& right);
	POD operator/(const POD& left, const POD& right);
	POD operator<(const POD& left, const POD& right);
	POD operator>(const POD& left, const POD& right);
	POD operator<=(const POD& left, const POD& right);
	POD operator>=(const POD& left, const POD& right);
	POD operator==(const POD& left, const POD& right);
	POD operator!=(const POD& left, const POD& right);

	POD operator&&(const POD& left, const POD& right);
	POD operator||(const POD& left, const POD& right);

	typedef std::map<std::string, S1::POD> MemoryTableData;

	struct MemoryTable {
		MemoryTableData data;

		S1::POD Lookup(const char* name);
		S1::POD Lookup(const std::string& name);
		void Define(const std::string& name, const S1::POD& pod);

		MemoryTable() {}

		friend std::ostream& operator<<(std::ostream& os, const MemoryTable& table);
	};
}