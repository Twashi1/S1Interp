#include "Token.h"

Token::Token() {
	this->data = 0;
	this->type = TokenType::NONE;
}

Token::Token(int data, TokenType type) {
	this->data = data;
	this->type = type;
}

Token::Token(char data, TokenType type) {
	this->data = data;
	this->type = type;
}


Token::Token(float data, TokenType type) {
	this->data = data;
	this->type = type;
}

Token::Token(std::string data, TokenType type) {
	this->data = data;
	this->type = type;
}


Token::Token(const Token& copy) {
	this->data = copy.data;
	this->type = copy.type;
}

std::ostream& operator<<(std::ostream& os, const TokenType& lex_type) {
	switch (lex_type) {
	case TokenType::NONE: os << "NONE"; break;
	case TokenType::END: os << "END"; break;
	case TokenType::INTEGER: os << "INTEGER"; break;
	case TokenType::INTEGER_LITERAL: os << "INTEGER_LITERAL"; break;
	case TokenType::FLOAT: os << "FLOAT"; break;
	case TokenType::FLOAT_LITERAL: os << "FLOAT_LITERAL"; break;
	case TokenType::STRING: os << "STRING"; break;
	case TokenType::STRING_LITERAL: os << "STRING_LITERAL"; break;
	case TokenType::ISTRING: os << "ISTRING"; break;
	case TokenType::ISTRING_LITERAL: os << "ISTRING_LITERAL"; break;
	case TokenType::BOOL: os << "BOOL"; break;
	case TokenType::TRUE: os << "TRUE"; break;
	case TokenType::FALSE: os << "FALSE"; break;
	case TokenType::PLUS: os << "PLUS"; break;
	case TokenType::MINUS: os << "MINUS"; break;
	case TokenType::MULTIPLY: os << "MULTIPLY"; break;
	case TokenType::DIVIDE: os << "DIVIDE"; break;
	case TokenType::LPAREN: os << "LPAREN"; break;
	case TokenType::RPAREN: os << "RPAREN"; break;
	case TokenType::ID: os << "ID"; break;
	case TokenType::ASSIGN: os << "ASSIGN"; break;
	case TokenType::SEMI: os << "SEMI"; break;
	case TokenType::LCURLY: os << "LCURLY"; break;
	case TokenType::RCURLY: os << "RCURLY"; break;
	case TokenType::BACKSLASH: os << "BACKSLASH"; break;
	case TokenType::BACKTICK: os << "BACKTICK"; break;
	case TokenType::COMMA: os << "COMMA"; break;
	case TokenType::COLON: os << "COLON"; break;
	case TokenType::DISPLAY: os << "DISPLAY"; break;
	case TokenType::QUOTES: os << "QUOTES"; break;
	case TokenType::RECEIVE: os << "RECEIVE"; break;
	case TokenType::AND: os << "AND"; break;
	case TokenType::OR: os << "OR"; break;
	case TokenType::WHILE: os << "WHILE"; break;
	case TokenType::IF: os << "IF"; break;
	case TokenType::FUNCTION: os << "FUNCTION"; break;
	case TokenType::MORE: os << "MORE"; break;
	case TokenType::NOTEQUALS: os << "NOTEQUALS"; break;

	default: os << "TokenType::" << (unsigned int)lex_type; break;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const TokenData& data) {
	switch (data.index()) {
	case 0: os << "char: " << std::get<char>(data); break;
	case 1: os << "int: " << std::get<int>(data); break;
	case 2: os << "float: " << std::get<float>(data); break;
	case 3: os << "string: " << std::get<std::string>(data); break;
	case 4: os << "bool: " << std::get<bool>(data); break;
	
	default: os << "Error"; break;
	}
	
	return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
	os << "Token(" << token.type << ", " << token.data << ")";
	return os;
}
