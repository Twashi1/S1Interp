#include "MemoryTable.h"

S1::POD S1::operator+(const POD& left, const POD& right) {
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) + std::get<0>(right); break;
	case 01: return std::get<0>(left) + std::get<1>(right); break;
	case 02: return std::get<0>(left) + std::get<2>(right); break;
	case 03: return std::get<0>(left) + std::get<3>(right); break;
	case 10: return std::get<1>(left) + std::get<0>(right); break;
	case 11: return std::get<1>(left) + std::get<1>(right); break;
	case 12: return std::get<1>(left) + std::get<2>(right); break;
	case 13: return std::get<1>(left) + std::get<3>(right); break;
	case 20: return std::get<2>(left) + std::get<0>(right); break;
	case 21: return std::get<2>(left) + std::get<1>(right); break;
	case 22: return std::get<2>(left) + std::get<2>(right); break;
	case 23: return std::get<2>(left) + std::get<3>(right); break;
	case 30: return std::get<3>(left) + std::get<0>(right); break;
	case 31: return std::get<3>(left) + std::get<1>(right); break;
	case 32: return std::get<3>(left) + std::get<2>(right); break;
	case 33: return std::get<3>(left) + std::get<3>(right); break;
	case 55: return std::get<5>(left) + std::get<5>(right); break;
	}
}

S1::POD S1::operator-(const POD& left, const POD& right) {
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) - std::get<0>(right); break;
	case 01: return std::get<0>(left) - std::get<1>(right); break;
	case 02: return std::get<0>(left) - std::get<2>(right); break;
	case 03: return std::get<0>(left) - std::get<3>(right); break;
	case 10: return std::get<1>(left) - std::get<0>(right); break;
	case 11: return std::get<1>(left) - std::get<1>(right); break;
	case 12: return std::get<1>(left) - std::get<2>(right); break;
	case 13: return std::get<1>(left) - std::get<3>(right); break;
	case 20: return std::get<2>(left) - std::get<0>(right); break;
	case 21: return std::get<2>(left) - std::get<1>(right); break;
	case 22: return std::get<2>(left) - std::get<2>(right); break;
	case 23: return std::get<2>(left) - std::get<3>(right); break;
	case 30: return std::get<3>(left) - std::get<0>(right); break;
	case 31: return std::get<3>(left) - std::get<1>(right); break;
	case 32: return std::get<3>(left) - std::get<2>(right); break;
	case 33: return std::get<3>(left) - std::get<3>(right); break;
	}
}

S1::POD S1::operator*(const POD& left, const POD& right) {
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) * std::get<0>(right); break;
	case 01: return std::get<0>(left) * std::get<1>(right); break;
	case 02: return std::get<0>(left) * std::get<2>(right); break;
	case 03: return std::get<0>(left) * std::get<3>(right); break;
	case 10: return std::get<1>(left) * std::get<0>(right); break;
	case 11: return std::get<1>(left) * std::get<1>(right); break;
	case 12: return std::get<1>(left) * std::get<2>(right); break;
	case 13: return std::get<1>(left) * std::get<3>(right); break;
	case 20: return std::get<2>(left) * std::get<0>(right); break;
	case 21: return std::get<2>(left) * std::get<1>(right); break;
	case 22: return std::get<2>(left) * std::get<2>(right); break;
	case 23: return std::get<2>(left) * std::get<3>(right); break;
	case 30: return std::get<3>(left) * std::get<0>(right); break;
	case 31: return std::get<3>(left) * std::get<1>(right); break;
	case 32: return std::get<3>(left) * std::get<2>(right); break;
	case 33: return std::get<3>(left) * std::get<3>(right); break;
	}
}

S1::POD S1::operator/(const POD& left, const POD& right) {
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) / std::get<0>(right); break;
	case 01: return std::get<0>(left) / std::get<1>(right); break;
	case 02: return std::get<0>(left) / std::get<2>(right); break;
	case 03: return std::get<0>(left) / std::get<3>(right); break;
	case 10: return std::get<1>(left) / std::get<0>(right); break;
	case 11: return std::get<1>(left) / std::get<1>(right); break;
	case 12: return std::get<1>(left) / std::get<2>(right); break;
	case 13: return std::get<1>(left) / std::get<3>(right); break;
	case 20: return std::get<2>(left) / std::get<0>(right); break;
	case 21: return std::get<2>(left) / std::get<1>(right); break;
	case 22: return std::get<2>(left) / std::get<2>(right); break;
	case 23: return std::get<2>(left) / std::get<3>(right); break;
	case 30: return std::get<3>(left) / std::get<0>(right); break;
	case 31: return std::get<3>(left) / std::get<1>(right); break;
	case 32: return std::get<3>(left) / std::get<2>(right); break;
	case 33: return std::get<3>(left) / std::get<3>(right); break;
	}
}

S1::POD S1::operator<(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) < std::get<0>(right); break;
	case 01: return std::get<0>(left) < std::get<1>(right); break;
	case 02: return std::get<0>(left) < std::get<2>(right); break;
	case 03: return std::get<0>(left) < std::get<3>(right); break;
	case 10: return std::get<1>(left) < std::get<0>(right); break;
	case 11: return std::get<1>(left) < std::get<1>(right); break;
	case 12: return std::get<1>(left) < std::get<2>(right); break;
	case 13: return std::get<1>(left) < std::get<3>(right); break;
	case 20: return std::get<2>(left) < std::get<0>(right); break;
	case 21: return std::get<2>(left) < std::get<1>(right); break;
	case 22: return std::get<2>(left) < std::get<2>(right); break;
	case 23: return std::get<2>(left) < std::get<3>(right); break;
	case 30: return std::get<3>(left) < std::get<0>(right); break;
	case 31: return std::get<3>(left) < std::get<1>(right); break;
	case 32: return std::get<3>(left) < std::get<2>(right); break;
	case 33: return std::get<3>(left) < std::get<3>(right); break;
	}
}

S1::POD S1::operator>(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) > std::get<0>(right); break;
	case 01: return std::get<0>(left) > std::get<1>(right); break;
	case 02: return std::get<0>(left) > std::get<2>(right); break;
	case 03: return std::get<0>(left) > std::get<3>(right); break;
	case 10: return std::get<1>(left) > std::get<0>(right); break;
	case 11: return std::get<1>(left) > std::get<1>(right); break;
	case 12: return std::get<1>(left) > std::get<2>(right); break;
	case 13: return std::get<1>(left) > std::get<3>(right); break;
	case 20: return std::get<2>(left) > std::get<0>(right); break;
	case 21: return std::get<2>(left) > std::get<1>(right); break;
	case 22: return std::get<2>(left) > std::get<2>(right); break;
	case 23: return std::get<2>(left) > std::get<3>(right); break;
	case 30: return std::get<3>(left) > std::get<0>(right); break;
	case 31: return std::get<3>(left) > std::get<1>(right); break;
	case 32: return std::get<3>(left) > std::get<2>(right); break;
	case 33: return std::get<3>(left) > std::get<3>(right); break;
	}
}

S1::POD S1::operator>=(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) >= std::get<0>(right); break;
	case 01: return std::get<0>(left) >= std::get<1>(right); break;
	case 02: return std::get<0>(left) >= std::get<2>(right); break;
	case 03: return std::get<0>(left) >= std::get<3>(right); break;
	case 10: return std::get<1>(left) >= std::get<0>(right); break;
	case 11: return std::get<1>(left) >= std::get<1>(right); break;
	case 12: return std::get<1>(left) >= std::get<2>(right); break;
	case 13: return std::get<1>(left) >= std::get<3>(right); break;
	case 20: return std::get<2>(left) >= std::get<0>(right); break;
	case 21: return std::get<2>(left) >= std::get<1>(right); break;
	case 22: return std::get<2>(left) >= std::get<2>(right); break;
	case 23: return std::get<2>(left) >= std::get<3>(right); break;
	case 30: return std::get<3>(left) >= std::get<0>(right); break;
	case 31: return std::get<3>(left) >= std::get<1>(right); break;
	case 32: return std::get<3>(left) >= std::get<2>(right); break;
	case 33: return std::get<3>(left) >= std::get<3>(right); break;
	}
}

S1::POD S1::operator<=(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) <= std::get<0>(right); break;
	case 01: return std::get<0>(left) <= std::get<1>(right); break;
	case 02: return std::get<0>(left) <= std::get<2>(right); break;
	case 03: return std::get<0>(left) <= std::get<3>(right); break;
	case 10: return std::get<1>(left) <= std::get<0>(right); break;
	case 11: return std::get<1>(left) <= std::get<1>(right); break;
	case 12: return std::get<1>(left) <= std::get<2>(right); break;
	case 13: return std::get<1>(left) <= std::get<3>(right); break;
	case 20: return std::get<2>(left) <= std::get<0>(right); break;
	case 21: return std::get<2>(left) <= std::get<1>(right); break;
	case 22: return std::get<2>(left) <= std::get<2>(right); break;
	case 23: return std::get<2>(left) <= std::get<3>(right); break;
	case 30: return std::get<3>(left) <= std::get<0>(right); break;
	case 31: return std::get<3>(left) <= std::get<1>(right); break;
	case 32: return std::get<3>(left) <= std::get<2>(right); break;
	case 33: return std::get<3>(left) <= std::get<3>(right); break;
	}
}

S1::POD S1::operator==(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) == std::get<0>(right); break;
	case 01: return std::get<0>(left) == std::get<1>(right); break;
	case 02: return std::get<0>(left) == std::get<2>(right); break;
	case 03: return std::get<0>(left) == std::get<3>(right); break;
	case 10: return std::get<1>(left) == std::get<0>(right); break;
	case 11: return std::get<1>(left) == std::get<1>(right); break;
	case 12: return std::get<1>(left) == std::get<2>(right); break;
	case 13: return std::get<1>(left) == std::get<3>(right); break;
	case 20: return std::get<2>(left) == std::get<0>(right); break;
	case 21: return std::get<2>(left) == std::get<1>(right); break;
	case 22: return std::get<2>(left) == std::get<2>(right); break;
	case 23: return std::get<2>(left) == std::get<3>(right); break;
	case 30: return std::get<3>(left) == std::get<0>(right); break;
	case 31: return std::get<3>(left) == std::get<1>(right); break;
	case 32: return std::get<3>(left) == std::get<2>(right); break;
	case 33: return std::get<3>(left) == std::get<3>(right); break;
	case 44: return std::get<4>(left) == std::get<4>(right); break;
	case 55: return std::get<5>(left) == std::get<5>(right); break;
	}
}

S1::POD S1::operator!=(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) != std::get<0>(right); break;
	case 01: return std::get<0>(left) != std::get<1>(right); break;
	case 02: return std::get<0>(left) != std::get<2>(right); break;
	case 03: return std::get<0>(left) != std::get<3>(right); break;
	case 10: return std::get<1>(left) != std::get<0>(right); break;
	case 11: return std::get<1>(left) != std::get<1>(right); break;
	case 12: return std::get<1>(left) != std::get<2>(right); break;
	case 13: return std::get<1>(left) != std::get<3>(right); break;
	case 20: return std::get<2>(left) != std::get<0>(right); break;
	case 21: return std::get<2>(left) != std::get<1>(right); break;
	case 22: return std::get<2>(left) != std::get<2>(right); break;
	case 23: return std::get<2>(left) != std::get<3>(right); break;
	case 30: return std::get<3>(left) != std::get<0>(right); break;
	case 31: return std::get<3>(left) != std::get<1>(right); break;
	case 32: return std::get<3>(left) != std::get<2>(right); break;
	case 33: return std::get<3>(left) != std::get<3>(right); break;
	case 44: return std::get<4>(left) != std::get<4>(right); break;
	case 55: return std::get<5>(left) != std::get<5>(right); break;
	}
}

S1::POD S1::operator&&(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 44: return std::get<4>(left) && std::get<4>(right); break;
	}
}

S1::POD S1::operator||(const POD& left, const POD& right)
{
	switch (left.index() * 10 + right.index()) {
	case 44: return std::get<4>(left) || std::get<4>(right); break;
	}
}

S1::POD S1::MemoryTable::Lookup(const char* name)
{
	S1::POD pod = data.at(name);
	return pod;
}

S1::POD S1::MemoryTable::Lookup(const std::string& name)
{
	S1::POD pod = data.at(name);
	return pod;
}

void S1::MemoryTable::Define(const std::string& name, const S1::POD& pod)
{
	data[name] = pod;
}

namespace S1 {
	std::ostream& operator<<(std::ostream& os, const POD& num) {
		os << "POD(";
		switch (num.index()) {
		case 0:
			// int
			os << "int: " << std::get<int>(num);
			break;
		case 1:
			// float
			os << "float: " << std::get<float>(num);
			break;
		case 2:
			// double
			os << "double: " << std::get<double>(num);
			break;
		case 3:
			// long
			os << "long: " << std::get<long>(num);
			break;
		case 4:
			// bool
		{
			bool value = std::get<bool>(num);

			os << "bool: ";

			if (value) {
				os << "true";
			}
			else {
				os << "false";
			}
			break;
		}
		case 5:
			// string
			os << "string: " << std::get<std::string>(num);
			break;
		}
		os << ")";
		return os;
	}

	S1::POD& operator>>(std::istream& is, S1::POD& pod)
	{
		int raw;
		is >> raw;
		pod = S1::POD(raw);

		return pod;
	}

	std::string PODToStr(const POD& num) {
		std::stringstream str;

		switch (num.index()) {
		case 0:
			// int
			str << std::get<int>(num);
			break;
		case 1:
			// float
			str << std::get<float>(num);
			break;
		case 2:
			// double
			str << std::get<double>(num);
			break;
		case 3:
			// long
			str << std::get<long>(num);
			break;
		case 4:
			// bool
		{
			bool value = std::get<bool>(num);

			if (value) {
				str << "true";
			}
			else {
				str << "false";
			}
			break;
		}
		case 5:
			str << std::get<std::string>(num);
			break;
		}

		return str.str();
	}

	std::ostream& operator<<(std::ostream& os, const MemoryTable& table) {
		os << "{" << std::endl;

		for (const std::pair<std::string, S1::POD>& pair : table.data) {
			os << "    {" << pair.first << ": " << pair.second << "}" << std::endl;
		}
		os << "}";

		return os;
	}
}