#pragma once

#include <string>
#include "Token.h"

#include <map>

class Lexer {
	std::string code;
	char current_char;

public:
	std::map<std::string, Token> RESERVED_KEYWORDS = {};
	int pos = 0;
	int peek_pos = 0;

	Lexer(std::string& code);

	inline void Advance(void);
	inline char Peek(void);
	inline int CreateInteger(void);
	inline void SkipWhitespace(void);

	inline Token ID(void);

	inline void Info(const char* text) { std::cout << "[LEXER INFO]: " << text << std::endl; }
	
	Token GetNextToken(void);
};