#pragma once

#include <iostream>
#include <variant>

enum class TokenType : unsigned int {
	NONE,
	END,
	// types and type literals
	INTEGER, INTEGER_LITERAL,
	FLOAT, FLOAT_LITERAL,
	STRING, STRING_LITERAL,
	ISTRING, ISTRING_LITERAL,
	BOOL, TRUE, FALSE,
	VOID,
	// operators
	PLUS, MINUS, MULTIPLY, DIVIDE,
	LESS, MORE, LESSEQUALS, MOREEQUALS, EQUALS, NOTEQUALS, // <, >, <=, >=, ==, !=
	// bool ops
	AND, OR,
	// punctuation
	LPAREN, RPAREN, // ()
	BACKTICK,
	SEMI,
	LCURLY, RCURLY, // {}
	BACKSLASH,
	COMMA,
	COLON,
	QUOTES,
	// misc.
	ID,
	ASSIGN,
	DISPLAY,
	RECEIVE,
	FUNCTION,
	IF, ELSE
};

typedef std::variant<char, int, float, std::string, bool> TokenData;

std::ostream& operator<<(std::ostream& os, const TokenType& lex);
std::ostream& operator<<(std::ostream& os, const TokenData& data);

struct Token {
	TokenData data;
	TokenType type;

	Token();
	Token(const Token& copy);
	Token(char data, TokenType type);
	Token(int data, TokenType type);
	Token(float data, TokenType type);
	Token(std::string data, TokenType type);

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};