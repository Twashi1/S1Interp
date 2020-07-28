#include "SymbolTable.h"

S1::Symbol S1::SymbolTable::Lookup(const char* name)
{
	S1::Symbol symbol = data.at(name);
	return symbol;
}

S1::Symbol S1::SymbolTable::Lookup(const std::string& name)
{
	S1::Symbol symbol = data.at(name);
	return symbol;
}

void S1::SymbolTable::Define(const Symbol& symbol)
{
	switch (symbol.index()) {
	case 0:
		data[std::get<0>(symbol).name] = symbol;
		break;
	case 1:
		data[std::get<1>(symbol).name] = symbol;
		break;
	case 2:
		data[std::get<2>(symbol).name] = symbol;
		break;
	}
}

void S1::SymbolTable::Define(const std::string& name, const Symbol& symbol)
{
	data[name] = symbol;
}

namespace S1 {
	std::ostream& operator<<(std::ostream& os, const SymbolTable& table) {
		os << "{" << std::endl;

		for (const std::pair<std::string, S1::Symbol>& pair : table.data) {
			os << "    {" << pair.first << ": " << pair.second << "}" << std::endl;
		}
		os << "}";

		return os;
	}
}
