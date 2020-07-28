#include "Scope.h"

namespace S1 {
	std::ostream& S1::operator<<(std::ostream& os, const Scope& scope)
	{
		os << "\n| Memory  |\n" << scope.memory;
		os << "\n| Symbols |\n" << scope.symbols;

		return os;
	}
}
