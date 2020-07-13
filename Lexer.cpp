#include "Lexer.h"
#include <iostream>

Lexer::Lexer(std::string& code)
	: code(code), current_char(code[0])
{}

inline void Lexer::Advance(void) {
	pos++;

	if (pos > code.length() - 1) {
		current_char = (char)LEXER_TYPES::END;
	}
	else {
		current_char = code[pos];
	}
}

inline char Lexer::Peek(void) {
	peek_pos = pos + 1;

	if (peek_pos > code.length() - 1) {
		return (char)LEXER_TYPES::END;
	}
	else {
		return code[peek_pos];
	}
}

inline int Lexer::CreateInteger(void) {
	std::string result;

	while (isdigit(current_char) && current_char != (char)LEXER_TYPES::END) {
		result += current_char;
		Advance();
	}

	return stoi(result);
}

inline void Lexer::SkipWhitespace(void) {
	while (isspace(current_char) && current_char != (char)LEXER_TYPES::END) {
		Advance();
	}
}

inline Token Lexer::ID(void) {
	std::string result = "";

	while (isalnum(current_char) && current_char != (char)LEXER_TYPES::END) {
		result += current_char;
		Advance();
	}

	Token token = Token(result, LEXER_TYPES::ID);

	try { token = RESERVED_KEYWORDS.at(result); }
	catch (std::out_of_range& e) {}

	return token;
}

Token Lexer::GetNextToken(void) {
	// while current_char is not end of code/file

	while (current_char != (char)LEXER_TYPES::END) {
		// skip whitespaces
		if (isspace(current_char)) {
			SkipWhitespace();
			continue;
		}
		else if (isdigit(current_char)) {
			Info("Creating integer");
			return Token(CreateInteger(), LEXER_TYPES::INTEGER);
		}
		else if (isalpha(current_char)) {
			return ID();
		} else if (current_char == '=' && Peek() != '=') {
			Info("Creating assign");
			Advance();
			Advance();
			return Token('=', LEXER_TYPES::ASSIGN);
		} else {
			switch (current_char) {
			case '+':
				Info("Creating plus");
				Advance();
				return Token('+', LEXER_TYPES::PLUS);
				break;
			case '-':
				Info("Creating minus");
				Advance();
				return Token('-', LEXER_TYPES::MINUS);
				break;
			case '*':
				Info("Creating multiply");
				Advance();
				return Token('*', LEXER_TYPES::MULTIPLY);
				break;
			case '/':
				Info("Creating divide");
				Advance();
				return Token('/', LEXER_TYPES::DIVIDE);
				break;
			case '(':
				Info("Creating lparen");
				Advance();
				return Token('(', LEXER_TYPES::LPAREN);
				break;
			case ')':
				Info("Creating rparen");
				Advance();
				return Token(')', LEXER_TYPES::RPAREN);
				break;
			case ';':
				Info("Creating semi");
				Advance();
				return Token(';', LEXER_TYPES::SEMI);
			case '{':
				Info("Creating lcurly");
				Advance();
				return Token('{', LEXER_TYPES::LCURLY);
			case '}':
				Info("Creating rcurly");
				Advance();
				return Token('}', LEXER_TYPES::RCURLY);
			default:
				std::cout << "[LEXER ERROR] Couldn't recognise character < " << current_char << " >" << std::endl;
				Advance();
				return Token(0, LEXER_TYPES::END);
				break;
			}
		}
	}

	std::cout << "[LEXER INFO]: Returning control!" << std::endl;

	return Token(1, LEXER_TYPES::END);
}