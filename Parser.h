#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Token.h"
#include "Lexer.h"

#include "Node.h"

class Parser {
private:
	Lexer* lexer;
	Token current_token;

public:
	Parser();
	Parser(Lexer* lexer);

	S1::Node Expr();
	S1::Node Parse();

private:
	inline void Error(const char* text);
	inline void Info(const char* text) { std::cout << "[PARSER INFO]: " << text << std::endl; }

	inline S1::COMPOUND Program(void);
	inline S1::COMPOUND CompoundStatement(void);
	inline S1::ASSIGN AssignmentStatement(void);
	inline S1::VAR Variable(void);
	inline S1::NOOP Empty(void);

	std::vector<std::shared_ptr<S1::Node>> StatementList(void);
	inline S1::Node Statement(void);

	inline void Eat(LEXER_TYPES eat_type);

	inline S1::Node Term(void);
	inline S1::Node Factor(void);
};