#include "SymbolTable.h"
#include "Errors.h"

S1::Symbol S1::SymbolTable::Lookup(const char* name)
{
	try {
		S1::Symbol symbol = data.at(name);
		return symbol;
	}
	catch (std::out_of_range) {
		throw new S1::id_not_found(name);
	}
}

S1::Symbol S1::SymbolTable::Lookup(const std::string& name)
{
	try {
		S1::Symbol symbol = data.at(name);
		return symbol;
	}
	catch (std::out_of_range) {
		throw new S1::id_not_found(name);
	}
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
