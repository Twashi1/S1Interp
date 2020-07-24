#pragma once

#include <string>
#include "Token.h"
#include "Errors.h"

#include <map>

class Lexer {
	std::string code;
	char current_char;

public:
	std::map<std::string, Token> RESERVED_KEYWORDS = {
		{"int", Token("int", TokenType::INTEGER)},
		{"float", Token("float", TokenType::FLOAT)},
		{"string", Token("string", TokenType::STRING)},
		{"istring", Token("istring", TokenType::ISTRING)},
		{"bool", Token("bool", TokenType::BOOL)},
		{"display", Token("display", TokenType::DISPLAY)},
		{"receive", Token("receive", TokenType::RECEIVE)},
		{"function", Token("function", TokenType::FUNCTION)},
		{"true", Token("true", TokenType::TRUE)},
		{"false", Token("false", TokenType::FALSE)},
		{"or", Token("or", TokenType::OR)},
		{"and", Token("and", TokenType::AND)},
		{"if", Token("if", TokenType::IF)},
		{"else", Token("else", TokenType::ELSE)}
	};
	int pos = 0;
	int peek_pos = 0;
	int line_num = 0;
	int column_num = 0;

	Lexer(std::string& code);

	inline void Advance(void);
	inline char Peek(void);
	inline int CreateInteger(std::string& from);
	inline float CreateFloat(std::string& from);
	inline std::variant<int, float> CreateNumber();
	inline std::string CreateString(void);
	inline std::string CreateIString(void);
	inline void SkipWhitespace(void);
	inline void SkipComment(void);

	inline Token ID(void);
	
	Token GetNextToken(void);
};