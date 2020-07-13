#pragma once

#include <iostream>
#include <variant>

enum class LEXER_TYPES : unsigned int {
	NONE,
	END,
	INTEGER,
	PLUS, MINUS, MULTIPLY, DIVIDE,
	LPAREN, RPAREN, // ()
	ID,
	ASSIGN,
	SEMI,
	LCURLY, RCURLY // {}
};

typedef std::variant<char, int, float, std::string> TokenData;

std::ostream& operator<<(std::ostream& os, const TokenData& data);

struct Token {
	TokenData data;
	LEXER_TYPES type;

	Token();
	Token(const Token& copy);
	Token(char data, LEXER_TYPES type);
	Token(int data, LEXER_TYPES type);
	Token(float data, LEXER_TYPES type);
	Token(std::string data, LEXER_TYPES type);

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};