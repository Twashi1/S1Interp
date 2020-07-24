#include "Symbol.h"

S1::FuncSymbol::FuncSymbol(const std::string& name, const std::vector<S1::VarSymbol>& params)
	: name(name)
{
	this->params.reserve(params.size() * sizeof(std::shared_ptr<S1::VarSymbol>));

	for (const VarSymbol& sym : params) {
		this->params.emplace_back(std::make_shared<VarSymbol>(sym));
	}
}

namespace S1 {

	std::ostream& operator<<(std::ostream& os, const BuiltInTypeSymbol& symbol)
	{
		os << symbol.name;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const VarSymbol& symbol)
	{
		os << "<" << symbol.name << ":" << *symbol.type << ">";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const S1::Symbol& sym) {
		os << "SYMBOL(";
		switch (sym.index()) {
		case 0:
			os << "BuiltInTypeSymbol: " << std::get<S1::BuiltInTypeSymbol>(sym);
			break;
		case 1:
			os << "VarSymbol: " << std::get<S1::VarSymbol>(sym);
			break;
		}
		os << ")";

		return os;
	}
}
