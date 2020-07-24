#include "Parser.h"
#include "Logger.h"

Parser::Parser(Lexer* lexer)
	: lexer(lexer)
{
	current_token = lexer->GetNextToken();
}

inline void Parser::Eat(TokenType eat_type) {
	if (current_token.type == eat_type) {
		current_token = lexer->GetNextToken();
	} else {
		// raise error
		throw S1::unexpected_token(current_token, eat_type, lexer->line_num, lexer->column_num);
	}
}

inline S1::Node Parser::Factor(void) {
	Token token = current_token;

	S1::Node node;

	switch (token.type) {
	case TokenType::INTEGER_LITERAL:
	{
		Eat(TokenType::INTEGER_LITERAL);

		node = std::get<int>(token.data);

		break;
	}

	case TokenType::FLOAT_LITERAL:
	{
		Eat(TokenType::FLOAT_LITERAL);
		node = std::get<float>(token.data);

		break;
	}

	case TokenType::STRING_LITERAL:
	{
		Eat(TokenType::STRING_LITERAL);

		node = std::get<std::string>(token.data);

		break;
	}

	case TokenType::RECEIVE:
	{
		Eat(TokenType::RECEIVE);

		node = S1::RECEIVE();

		break;
	}

	case TokenType::ISTRING_LITERAL:
	{
		Eat(TokenType::ISTRING_LITERAL);

		std::string data = std::get<std::string>(token.data);

		int pos = 0;
		int max_pos = data.length();

		char peek_char = 0;
		char current_char = 0;
		char prev_char = 0;

		std::vector<S1::Node> nodes;
		std::string text;

		while (pos < max_pos) {
			prev_char = current_char;
			current_char = data[pos];
			peek_char = pos + 1 < max_pos ? data[pos + 1] : 0;

			if (current_char == '$' && prev_char != '\\' && peek_char == '{') {
				text += "$";

				pos += 2;
				prev_char = current_char;
				current_char = data[pos];

				std::string node_text = "";

				while (current_char != '}' && pos < max_pos) {
					node_text += current_char;
					pos++;
					prev_char = current_char;
					current_char = data[pos];
				}

				if (node_text != "") {
					// not good code
					Lexer node_lex(node_text);
					Parser parser(&node_lex);

					S1::Node expr_res = parser.Expr();

					nodes.emplace_back(expr_res);
				}
			}
			else {
				text += current_char;
			}
			
			pos++;
		}

		node = S1::ISTRING(text, nodes);
		break;
	}

	case TokenType::TRUE:
	{
		Eat(TokenType::TRUE);

		node = true;

		break;
	}

	case TokenType::FALSE:
	{
		Eat(TokenType::FALSE);

		node = false;

		break;
	}

	case TokenType::LPAREN:
	{
		Eat(TokenType::LPAREN);

		node = Expr();

		Eat(TokenType::RPAREN);

		break;
	}

	case TokenType::PLUS:
	{
		Eat(TokenType::PLUS);

		node = S1::UNARYOP_ADD(Factor());

		break;
	}

	case TokenType::MINUS:
	{
		Eat(TokenType::MINUS);

		node = S1::UNARYOP_MIN(Factor());

		break;
	}

	default:
	{
		node = Variable();
		break;
	}
	}

	return node;
}

inline S1::Node Parser::Term(void) {
	S1::Node node = Factor();

	while (current_token.type == TokenType::MULTIPLY || current_token.type == TokenType::DIVIDE) {
		Token token = current_token;

		switch (token.type) {
		case TokenType::MULTIPLY:
			Eat(TokenType::MULTIPLY);

			node = S1::BINOP_MUL(node, Factor());

			break;

		case TokenType::DIVIDE:
			Eat(TokenType::DIVIDE);

			node = S1::BINOP_DIV(node, Factor());

			break;
		}
	}

	return node;
}

S1::Node Parser::Expr() {
	S1::Node node = Term();

	bool continue_loop = true;

	while (continue_loop) {
		Token token = current_token;

		switch (token.type) {
		case TokenType::PLUS:
		{
			Eat(TokenType::PLUS);

			S1::Node copy(node);

			node = S1::BINOP_ADD(copy, Term());

			break;
		}

		case TokenType::MINUS:
		{
			Eat(TokenType::MINUS);

			S1::Node copy(node);

			node = S1::BINOP_MIN(copy, Term());

			break;
		}

		case TokenType::EQUALS:
		{
			Eat(TokenType::EQUALS);

			S1::Node copy(node);
			
			node = S1::BINOP_EQ(copy, Factor());

			break;
		}

		case TokenType::NOTEQUALS:
		{
			Eat(TokenType::NOTEQUALS);

			S1::Node copy(node);

			node = S1::BINOP_NEQ(copy, Factor());

			break;
		}

		case TokenType::MORE:
		{
			Eat(TokenType::NOTEQUALS);

			S1::Node copy(node);

			node = S1::BINOP_ME(copy, Factor());

			break;
		}

		case TokenType::LESS:
		{
			Eat(TokenType::LESS);

			S1::Node copy(node);

			node = S1::BINOP_LE(copy, Factor());

			break;
		}

		case TokenType::LESSEQUALS:
		{
			Eat(TokenType::LESSEQUALS);

			S1::Node copy(node);

			node = S1::BINOP_LEQ(copy, Factor());

			break;
		}

		case TokenType::MOREEQUALS:
		{
			Eat(TokenType::MOREEQUALS);

			S1::Node copy(node);

			node = S1::BINOP_MEQ(copy, Factor());

			break;
		}

		case TokenType::AND:
		{
			Eat(TokenType::AND);

			S1::Node copy(node);

			node = S1::BINOP_AND(copy, Factor());

			break;
		}

		case TokenType::OR:
		{
			Eat(TokenType::OR);

			S1::Node copy(node);

			node = S1::BINOP_OR(copy, Factor());

			break;
		}

		default:
			continue_loop = false;
			break;
		}
	}

	return node;
}

S1::Node Parser::Parse() {
	return Program();
}

inline S1::PROGRAM Parser::Program(void)
{
	std::vector<std::shared_ptr<S1::Node>> compound_statements;

	compound_statements = StatementList();
	S1::COMPOUND compound = S1::COMPOUND(compound_statements);
	S1::PROGRAM program = S1::PROGRAM("DEFAULT", compound); // TODO: Name for the program should be the path

	return program;
}

inline S1::COMPOUND Parser::CompoundStatement(void)
{
	Eat(TokenType::LCURLY);

	std::vector<std::shared_ptr<S1::Node>> statements = StatementList();

	Eat(TokenType::RCURLY);

	S1::COMPOUND root = S1::COMPOUND(statements);

	return root;
}

std::vector<std::shared_ptr<S1::Node>> Parser::AssignmentStatements(const std::vector<std::shared_ptr<S1::VAR>>& var_list)
{
	Eat(TokenType::ASSIGN);

	S1::Node right = Expr();

	std::vector<std::shared_ptr<S1::Node>> assignment_statements;

	for (std::shared_ptr<S1::VAR> var : var_list) {
		assignment_statements.emplace_back(std::make_shared<S1::Node>((S1::Node)S1::ASSIGN(*var, right)));
	}

	return assignment_statements;
}

inline S1::IF Parser::IfStatement(void)
{
	Eat(TokenType::IF);

	// expecting ( condition )

	Eat(TokenType::LPAREN); // (

	S1::Node condition = Expr(); // now expecting condition

	Eat(TokenType::RPAREN); // )

	// now expecting compound

	S1::COMPOUND compound = CompoundStatement();

	switch (current_token.type) {
	case TokenType::SEMI: // end of the if statement (chain)
	{
		S1::IF if_statement = S1::IF(condition, compound);
		return if_statement;
		break;
	}

	case TokenType::ELSE:
	{
		// eat the else
		Eat(TokenType::ELSE);

		// now we can either get a compound, or another if statement:
		// | else {};
		// | else if () {}

		switch (current_token.type) {
		case TokenType::LCURLY: // its an empty else
		{
			S1::COMPOUND else_compound = CompoundStatement(); // create the compound

			S1::IF else_statement = S1::IF((S1::Node)true, else_compound);

			S1::IF if_statement = S1::IF(condition, compound, std::make_shared<S1::IF>(else_statement));

			return if_statement;
			break;
		}

		case TokenType::IF: // its an elif
		{
			S1::IF chained_if = IfStatement();
			S1::IF if_statement = S1::IF(condition, compound, std::make_shared<S1::IF>(chained_if));
			
			return if_statement;
			break;
		}
		}
		break;
	}
	}
}

inline S1::VAR Parser::Variable(void)
{
	S1::VAR var = S1::VAR(current_token);
	Eat(TokenType::ID);
	return var;
}

inline S1::NOOP Parser::Empty(void)
{
	return S1::NOOP();
}

inline S1::TYPE Parser::TypeSpecification(void)
{
	Token token = current_token;

	// amazing programming right here
	switch (current_token.type) {
	case TokenType::INTEGER:
		Eat(TokenType::INTEGER);
		break;

	case TokenType::FLOAT:
		Eat(TokenType::FLOAT);
		break;

	case TokenType::STRING:
		Eat(TokenType::STRING);
		break;

	case TokenType::ISTRING:
		Eat(TokenType::ISTRING);
		break;

	case TokenType::BOOL:
		Eat(TokenType::BOOL);
		break;

	case TokenType::VOID:
		Eat(TokenType::VOID);
		break;
	}

	S1::TYPE type = S1::TYPE(token);

	return type;
}

std::vector<std::shared_ptr<S1::Node>> Parser::StatementList(void)
{
	std::vector<std::shared_ptr<S1::Node>> statements;
	bool skip_first = false;

	if (current_token.type != TokenType::ID) {
		S1::Node first = Statement();
		statements.emplace_back(std::make_shared<S1::Node>(first));
	}
	else {
		skip_first = true;
	}

	while (current_token.type == TokenType::SEMI || skip_first) {
		if (!skip_first) { Eat(TokenType::SEMI); }
		skip_first = false;

		switch (current_token.type) {
		case TokenType::ID:
		{
			std::vector<std::shared_ptr<S1::VAR>> vars;
			S1::VAR first(current_token);
			vars.emplace_back(std::make_shared<S1::VAR>(first));
			Eat(TokenType::ID);

			while (current_token.type == TokenType::COMMA) {
				Eat(TokenType::COMMA);
				vars.emplace_back(std::make_shared<S1::VAR>(S1::VAR(current_token)));
				Eat(TokenType::ID);
			}

			std::vector<std::shared_ptr<S1::Node>> nodes;

			switch (current_token.type) {
			case TokenType::ASSIGN:
				nodes = AssignmentStatements(vars);
				break;

			case TokenType::COLON:
				nodes = VarDeclarations(vars);
				break;
			}

			statements.insert(statements.end(), nodes.begin(), nodes.end());
		}

		default:
			statements.emplace_back(std::make_shared<S1::Node>(Statement()));
			break;
		}
	}

	return statements;
}

inline S1::PARAM Parser::Parameter(void)
{
	// get var
	S1::VAR var = S1::VAR(current_token);
	Eat(TokenType::ID);

	// expecting a colon, since syntax is var_name:type_name
	Eat(TokenType::COLON);

	// expecting a type, so generate a type
	S1::TYPE type = TypeSpecification();

	// create param
	S1::PARAM param = S1::PARAM(var, type);

	return param;
}

std::vector<std::shared_ptr<S1::PARAM>> Parser::ParamList(void)
{
	std::vector<std::shared_ptr<S1::PARAM>> params;

	Eat(TokenType::LPAREN);

	// get the first parameter
	S1::PARAM first = Parameter();

	params.emplace_back(std::make_shared<S1::PARAM>(first));

	while (current_token.type == TokenType::COMMA) {
		Eat(TokenType::COMMA);

		// if we got a comma, start parsing the next parameter
		params.emplace_back(std::make_shared<S1::PARAM>(Parameter()));
	}

	// finished parsing params
	return params; // TODO: should probably pass a reference
}

S1::Node Parser::CreateFunction(void)
{
	Eat(TokenType::FUNCTION);

	S1::Node node;

	// get parameters
	std::vector<std::shared_ptr<S1::PARAM>> params = ParamList();
	Eat(TokenType::RPAREN);

	// get name
	std::string name = std::get<std::string>(current_token.data);
	Eat(TokenType::ID);

	// syntax is name:type, therefore we need to eat a colon
	Eat(TokenType::COLON);

	// get type
	S1::TYPE type = TypeSpecification();

	switch (current_token.type) {
	case TokenType::LCURLY: // function definition
	{
		// create compound
		S1::COMPOUND compound = CompoundStatement();
		// create funcdef
		S1::FUNCDEF func_def = S1::FUNCDEF(name, type, compound, params);

		node = S1::Node(func_def);
		break;
	}

	case TokenType::SEMI: // function declaration
	{
		// create funcdecl
		S1::FUNCDECL func_decl = S1::FUNCDECL(name, type, params);

		node = S1::Node(func_decl);
		break;
	}
	}

	return node;
}

inline S1::Node Parser::Statement(void)
{
	S1::Node node;

	switch (current_token.type) {
	case TokenType::LCURLY:
	{
		node = CompoundStatement();
		break;
	}

	case TokenType::DISPLAY:
	{
		Eat(TokenType::DISPLAY);
		node = S1::DISPLAY(Expr());
		break;
	}

	case TokenType::FUNCTION:
	{
		node = CreateFunction();
		break;
	}

	case TokenType::IF:
	{
		node = IfStatement();
		break;
	}

	default:
		node = Empty();
		break;
	}

	return node;
}

std::vector<std::shared_ptr<S1::Node>> Parser::VarDeclarations(const std::vector<std::shared_ptr<S1::VAR>>& var_list)
{
	Eat(TokenType::COLON);

	std::shared_ptr<S1::TYPE> type_node = std::make_shared<S1::TYPE>(TypeSpecification());

	S1::Node assign_value = (S1::Node)S1::NOOP();

	bool gen_assign = false;

	if (current_token.type == TokenType::ASSIGN) {
		Eat(TokenType::ASSIGN);
		gen_assign = true;
		assign_value = (S1::Node)Expr();
	}

	std::vector<std::shared_ptr<S1::Node>> nodes;

	unsigned int num_instances = var_list.size();

	if (gen_assign) {
		num_instances *= 2;
	}

	nodes.reserve(sizeof(std::shared_ptr<S1::Node>) * num_instances);

	for (std::shared_ptr<S1::VAR> var_node : var_list) {
		S1::VARDECL decl = S1::VARDECL(var_node, type_node);

		if (gen_assign) {
			S1::Node new_assign = (S1::Node)S1::ASSIGN(*var_node, assign_value);
			nodes.emplace_back(std::make_shared<S1::Node>(new_assign));
		}

		nodes.emplace_back(std::make_shared<S1::Node>(S1::Node(decl)));
	}

	return nodes;
}
