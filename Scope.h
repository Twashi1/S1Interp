#pragma once

#include "MemoryTable.h"
#include "SymbolTable.h"

namespace S1 {
	struct Scope {
		MemoryTable memory;
		SymbolTable symbols;

		Scope() {}
		Scope(const Scope& copy) : memory(copy.memory), symbols(copy.symbols) {}

		friend std::ostream& operator<<(std::ostream& os, const Scope& scope);
	};

	std::ostream& operator<<(std::ostream& os, const Scope& scope);
}