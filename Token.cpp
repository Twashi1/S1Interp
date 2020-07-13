#include "Token.h"

Token::Token() {
	this->data = 0;
	this->type = LEXER_TYPES::NONE;
}

Token::Token(int data, LEXER_TYPES type) {
	this->data = data;
	this->type = type;
}

Token::Token(char data, LEXER_TYPES type) {
	this->data = data;
	this->type = type;
}


Token::Token(float data, LEXER_TYPES type) {
	this->data = data;
	this->type = type;
}

Token::Token(std::string data, LEXER_TYPES type) {
	this->data = data;
	this->type = type;
}


Token::Token(const Token& copy) {
	this->data = copy.data;
	this->type = copy.type;
}

std::ostream& operator<<(std::ostream& os, const LEXER_TYPES& lex_type) {
	switch (lex_type) {
	case LEXER_TYPES::NONE:
		os << "Lexer::NONE";
		return os;
		break;

	case LEXER_TYPES::END:
		os << "Lexer::END";
		return os;
		break;

	case LEXER_TYPES::INTEGER:
		os << "Lexer::INTEGER";
		return os;
		break;

	case LEXER_TYPES::PLUS:
		os << "Lexer::PLUS";
		return os;
		break;

	case LEXER_TYPES::MINUS:
		os << "Lexer::MINUS";
		break;

	case LEXER_TYPES::MULTIPLY:
		os << "Lexer::MULTIPLY";
		return os;
		break;

	case LEXER_TYPES::DIVIDE:
		os << "Lexer::DIVIDE";
		return os;
		break;

	case LEXER_TYPES::LPAREN:
		os << "Lexer::LPAREN";
		return os;
		break;

	case LEXER_TYPES::RPAREN:
		os << "Lexer::RPAREN";
		return os;
		break;

	case LEXER_TYPES::ID:
		os << "Lexer::ID";
		return os;
		break;

	case LEXER_TYPES::ASSIGN:
		os << "Lexer::ASSIGN";
		return os;
		break;

	case LEXER_TYPES::SEMI:
		os << "Lexer::SEMI";
		return os;
		break;

	case LEXER_TYPES::LCURLY:
		os << "Lexer::LCURLY";
		return os;
		break;

	case LEXER_TYPES::RCURLY:
		os << "Lexer::RCURLY";
		return os;
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const TokenData& data) {
	switch (data.index()) {
	case 0:
		os << "Token(" << "char: " << std::get<char>(data) << ")";
		break;
	case 1:
		os << "Token(" << "int: " << std::get<int>(data) << ")";
		break;
	case 2:
		os << "Token(" << "float: " << std::get<float>(data) << ")";
		break;
	case 3:
		os << "Token(" << "string: " << std::get<std::string>(data) << ")";
		break;
	default:
		os << "Token(" << "err: " << "err" << ")";
		break;
	}
	
	return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
	os << "Token(" << token.type << ", " << token.data << ")";
	return os;
}
