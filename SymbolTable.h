#pragma once

#include "Symbol.h"

namespace S1 {
	typedef std::map<std::string, Symbol> SymbolTableData;

	struct SymbolTable {
		SymbolTableData data = {
			{ "int", BuiltInTypeSymbol("int") },
			{ "float", BuiltInTypeSymbol("float") },
			{ "string", BuiltInTypeSymbol("string") },
			{ "istring", BuiltInTypeSymbol("istring") },
			{ "bool", BuiltInTypeSymbol("bool") },
			{ "void", BuiltInTypeSymbol("void") }
		};

		Symbol Lookup(const char* name);
		Symbol Lookup(const std::string& name);
		void Define(const Symbol& symbol);
		void Define(const std::string& name, const Symbol& symbol);

		SymbolTable() {}

		friend std::ostream& operator<<(std::ostream& os, const SymbolTable& table);
	};
}