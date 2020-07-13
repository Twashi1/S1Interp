#include "Parser.h"
#include "Logger.h"

Parser::Parser() { lexer = nullptr; }

Parser::Parser(Lexer* lexer)
	: lexer(lexer)
{
	Info("Getting New Token...");
	current_token = lexer->GetNextToken();
}

inline void Parser::Eat(LEXER_TYPES eat_type) {
	if (current_token.type == eat_type) {
		Info("Getting New Token...");
		current_token = lexer->GetNextToken();
	}
	else {
		// raise error
		std::cout << "[PARSER ERROR]: [Parser::Eat] Expected type: " << (int)eat_type << " but got " << (int)current_token.type << std::endl;
	}
}

inline S1::Node Parser::Factor(void) {
	Token token = current_token;

	switch (token.type) {
	case LEXER_TYPES::INTEGER:
	{
		Info("Factoring int...");
		Eat(LEXER_TYPES::INTEGER);

		S1::Node integer(std::get<int>(token.data));

		return S1::Node(integer);
		break;
	}

	case LEXER_TYPES::LPAREN:
	{
		Info("Factoring parenthesis...");
		Eat(LEXER_TYPES::LPAREN);

		S1::Node node = Expr();

		Eat(LEXER_TYPES::RPAREN);
		return (S1::Node)node;
		break;
	}

	case LEXER_TYPES::PLUS:
	{
		Info("Factoring plus...");
		Eat(LEXER_TYPES::PLUS);
		S1::Node node = S1::UNARYOP_ADD(Factor());
		return node;
		break;
	}

	case LEXER_TYPES::MINUS:
	{
		Info("Factoring minus...");
		Eat(LEXER_TYPES::MINUS);
		S1::Node node = S1::UNARYOP_MIN(Factor());
		return node;
		break;
	}

	default:
	{
		Info("Factoring variable...");
		S1::Node node = Variable();
		return node;
		break;
	}
	}
}

inline S1::Node Parser::Term(void) {
	S1::Node node = Factor();

	while (current_token.type == LEXER_TYPES::MULTIPLY || current_token.type == LEXER_TYPES::DIVIDE) {
		Token token = current_token;

		switch (token.type) {
		case LEXER_TYPES::MULTIPLY:
			Info("Term multiply");
			Eat(LEXER_TYPES::MULTIPLY);
			node = S1::BINOP_MUL(node, Factor());
			break;

		case LEXER_TYPES::DIVIDE:
			Info("Term divide");
			Eat(LEXER_TYPES::DIVIDE);
			node = S1::BINOP_DIV(node, Factor());
			break;
		}
	}

	return node;
}

S1::Node Parser::Expr() {
	S1::Node node = Term();

	while (current_token.type == LEXER_TYPES::PLUS || current_token.type == LEXER_TYPES::MINUS) {
		Token token = current_token;

		switch (token.type) {
		case LEXER_TYPES::PLUS:
		{
			Info("Expr plus");
			Eat(LEXER_TYPES::PLUS);
			S1::Node copy(node);
			node = S1::BINOP_ADD(copy, Term());
			break;
		}

		case LEXER_TYPES::MINUS:
		{
			Info("Expr minus");
			Eat(LEXER_TYPES::MINUS);
			S1::Node copy(node);
			node = S1::BINOP_MIN(copy, Term());
			break;
		}
		}
	}

	return node;
}

S1::Node Parser::Parse() {
	Info("About to create program!");
	S1::Node node = Program();
	Info("Created program!");

	return node;
}

inline void Parser::Error(const char* text)
{
	std::cout << "[PARSER ERROR]: " << text << std::endl;
}

inline S1::COMPOUND Parser::Program(void)
{
	std::vector<std::shared_ptr<S1::Node>> program_statements;

	program_statements = StatementList();

	std::cout << "StatementList has size: " << program_statements.size() << std::endl;

	S1::COMPOUND program = S1::COMPOUND(program_statements);

	Info("Generated program!");

	return program;
}

inline S1::COMPOUND Parser::CompoundStatement(void)
{
	Eat(LEXER_TYPES::LCURLY);
	
	Info("Generating CompoundStatement!");

	std::vector<std::shared_ptr<S1::Node>> statements = StatementList();

	std::cout << "CompoundStatement statements list has size of: " << statements.size() << std::endl;

	Eat(LEXER_TYPES::RCURLY);

	S1::COMPOUND root = S1::COMPOUND(statements);

	return root;
}

inline S1::ASSIGN Parser::AssignmentStatement(void)
{
	S1::VAR left = Variable();
	
	Eat(LEXER_TYPES::ASSIGN);

	S1::Node right = Expr();

	S1::ASSIGN assignment = S1::ASSIGN(left, right);

	return assignment;
}

inline S1::VAR Parser::Variable(void)
{
	S1::VAR var = S1::VAR(current_token);
	Eat(LEXER_TYPES::ID);
	return var;
}

inline S1::NOOP Parser::Empty(void)
{
	return S1::NOOP();
}

std::vector<std::shared_ptr<S1::Node>> Parser::StatementList(void)
{
	Info("Generating Generic Statement List");
	std::vector<std::shared_ptr<S1::Node>> statements;

	S1::Node first = Statement();
	statements.emplace_back(std::make_shared<S1::Node>(first));

	std::cout << "In Parser::StatementList, current token is: " << current_token << std::endl;

	while (current_token.type == LEXER_TYPES::SEMI) {
		Eat(LEXER_TYPES::SEMI);
		statements.emplace_back(std::make_shared<S1::Node>(Statement()));
	}

	if (current_token.type == LEXER_TYPES::ID) {
		Error("[Parser::StatementList] Current token type is LEXER_TYPES::ID!");
	}

	return statements;
}

inline S1::Node Parser::Statement(void)
{
	S1::Node node;

	switch (current_token.type) {
	case LEXER_TYPES::LCURLY:
	{
		Info("[Parser::Statement] Creating Compound");
		node = CompoundStatement();
		break;
	}
	case LEXER_TYPES::ID:
	{
		Info("[Parser::Statement] Creating Assignment");
		node = AssignmentStatement();
		break;
	}
	default:
		Info("[Parser::Statement] Creating NoOp");
		node = Empty();
		break;
	}

	return node;
}
