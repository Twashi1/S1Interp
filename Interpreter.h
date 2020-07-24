#pragma once

#include <sstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "Node.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "MemoryTable.h"
#include "Scope.h"

namespace S1 {
	typedef std::vector<std::shared_ptr<Scope>> ScopeVector;
	std::ostream& operator<<(std::ostream& os, const ScopeVector& scope_vec);

	struct Interpreter {
		std::shared_ptr<Scope> current_scope = std::make_shared<Scope>(Scope());
		int current_scope_level = 0;

		std::map<int, ScopeVector> scopes = {
			{0, ScopeVector{current_scope}}
		};

		Parser* parser;

		S1::POD Interpret() {
			return std::visit(*this, parser->Parse());
		}

		Interpreter(Parser* parser) : parser(parser) {}

		POD operator()(const int& visitee) { return (POD)visitee; }
		POD operator()(const bool& visitee) { return (POD)visitee; }
		POD operator()(const long& visitee) { return (POD)visitee; }
		POD operator()(const float& visitee) { return (POD)visitee; }
		POD operator()(const double& visitee) { return (POD)visitee; }
		POD operator()(const std::string& visitee) { return (POD)visitee; }
		POD operator()(const ISTRING& visitee);

		// raw types, should never be visited
		POD operator()(const UNARYOP& visitee);
		POD operator()(const BINOP& visitee);

		POD operator()(const BINOP_ADD& visitee);
		POD operator()(const BINOP_MIN& visitee);
		POD operator()(const BINOP_MUL& visitee);
		POD operator()(const BINOP_DIV& visitee);

		POD operator()(const BINOP_EQ& visitee);
		POD operator()(const BINOP_NEQ& visitee);
		POD operator()(const BINOP_MEQ& visitee);
		POD operator()(const BINOP_LEQ& visitee);
		POD operator()(const BINOP_LE& visitee);
		POD operator()(const BINOP_ME& visitee);

		POD operator()(const BINOP_AND& visitee);
		POD operator()(const BINOP_OR& visitee);

		POD operator()(const UNARYOP_ADD& visitee);
		POD operator()(const UNARYOP_MIN& visitee);

		POD operator()(const COMPOUND& visitee);
		POD operator()(const ASSIGN& visitee);
		POD operator()(const VAR& visitee);

		POD operator()(const NOOP& visitee);

		POD operator()(const PROGRAM& visitee);

		POD operator()(const VARDECL& visitee);
		POD operator()(const TYPE& visitee);

		POD operator()(const DISPLAY& visitee);
		POD operator()(const RECEIVE& visitee);

		POD operator()(const FUNCDECL& visitee);
		POD operator()(const FUNCDEF& visitee);

		POD operator()(const PARAM& visitee);

		POD operator()(const IF& visitee);

		void __Format(int pos, std::string& text, std::shared_ptr<S1::Node> node);
		void __AddScope(void);

		Symbol __SearchSymbol(const char* var_name);
		POD __SearchMemory(const char* var_name);

		void PrintScopes(void);
	};
}