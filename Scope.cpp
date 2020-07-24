#include "Scope.h"

namespace S1 {
	std::ostream& S1::operator<<(std::ostream& os, const Scope& scope)
	{
		os << "\n| Memory: " << scope.memory;
		os << "\n| Symbols: " << scope.symbols;

		return os;
	}
}
