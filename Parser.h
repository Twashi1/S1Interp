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
	Parser(Lexer* lexer);

	S1::Node Expr();
	S1::Node Parse();

private:
	inline S1::PROGRAM Program(void);

	inline S1::COMPOUND CompoundStatement(void);
	inline S1::IF IfStatement(void);
	inline S1::WHILE WhileStatement(void);
	inline S1::Node IDStatement(void);
	inline S1::Node VarDeclaration(const S1::VAR& var);

	std::vector<std::shared_ptr<S1::Node>> AssignmentStatements(const std::vector<std::shared_ptr<S1::VAR>>& var_list, const S1::Node& right);
	std::vector<std::shared_ptr<S1::Node>> VarDeclarations(const std::vector<std::shared_ptr<S1::VAR>>& var_list);
	std::vector<std::shared_ptr<S1::VAR>> ParseIDList(const S1::VAR& first);

	inline S1::Node Statement(void);
	inline S1::NOOP Empty(void);
	inline S1::Node FunctionCall(void);

	inline S1::TYPE TypeSpecification(void);

	std::vector<std::shared_ptr<S1::Node>> StatementList(void);

	inline S1::PARAM Parameter(void);
	std::vector<std::shared_ptr<S1::PARAM>> ParamList(void);

	S1::Node CreateFunction(void);

	inline void Eat(TokenType eat_type);

	inline S1::Node Term(void);
	inline S1::Node Factor(void);
};