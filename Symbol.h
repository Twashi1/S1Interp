#pragma once

#include <string>
#include <memory>
#include <map>
#include <variant>
#include <iostream>
#include <vector>

namespace S1 {
	struct BuiltInTypeSymbol;
	struct VarSymbol;
	struct FuncSymbol;

	typedef std::variant<BuiltInTypeSymbol, VarSymbol, FuncSymbol> Symbol;

	struct BuiltInTypeSymbol {
		std::string name = "NULL";
		
		BuiltInTypeSymbol() {}
		BuiltInTypeSymbol(const std::string& name) : name(name) {}
		BuiltInTypeSymbol(const char* name) { this->name = std::string(name); }
		BuiltInTypeSymbol(const BuiltInTypeSymbol& copy) { name = copy.name; }

		bool operator==(const BuiltInTypeSymbol& compare) {
			if (name == compare.name) {
				return true;
			}

			return false;
		}
	};

	struct VarSymbol {
		std::string name = "NULL";
		std::shared_ptr<BuiltInTypeSymbol> type = nullptr;

		VarSymbol() {}
		VarSymbol(const std::string& name, const BuiltInTypeSymbol& type)
			: name(name), type(std::make_shared<BuiltInTypeSymbol>(type))
		{}
		VarSymbol(const char* name, const BuiltInTypeSymbol& type)
			: name(std::string(name)), type(std::make_shared<BuiltInTypeSymbol>(type))
		{}
		VarSymbol(const VarSymbol& copy)
			: name(copy.name), type(copy.type)
		{}
	};

	struct FuncSymbol {
		std::string name = "NULL";
		std::vector<std::shared_ptr<VarSymbol>> params;

		FuncSymbol() {}
		FuncSymbol(const std::string& name, const std::vector<std::shared_ptr<VarSymbol>>& params)
			: name(name), params(params)
		{}
		FuncSymbol(const std::string& name, const std::vector<VarSymbol>& params);
	};

	std::ostream& operator<<(std::ostream& os, const BuiltInTypeSymbol& symbol);
	std::ostream& operator<<(std::ostream& os, const VarSymbol& symbol);
	std::ostream& operator<<(std::ostream& os, const Symbol& symbol);
}