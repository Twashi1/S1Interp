#include "Lexer.h"
#include <iostream>

Lexer::Lexer(std::string& code)
	: code(code), current_char(code[0])
{}

inline void Lexer::Advance(void) {
	pos++;


	if (code[pos - 1] == '\\' && current_char == 'n') {
		line_num++;
		column_num = 0;
	}

	if (pos > code.length() - 1) {
		current_char = (char)TokenType::END;
	}
	else {
		current_char = code[pos];
		column_num++;
	}
}

inline char Lexer::Peek(void) {
	peek_pos = pos + 1;

	if (peek_pos > code.length() - 1) {
		return (char)TokenType::NONE;
	}
	else {
		return code[peek_pos];
	}
}

inline std::variant<int, float> Lexer::CreateNumber() {
	std::string number_string;
	bool makeFloat = false;

	// while we haven't hit the end of the code
	// and the current_char is either a digit or a decimal point
	while (
		current_char != (char)TokenType::END &&
		(isdigit(current_char) || current_char == '.')
	)
	{
		// add to number string
		number_string += current_char;
		// check again if current_char is a '.' (laggy?)
		if (current_char == '.') {
			// we gotta make a float
			makeFloat = true;
		}

		Advance();
	}

	if (makeFloat) {
		return CreateFloat(number_string);
	}
	else {
		return CreateInteger(number_string);
	}
}

inline std::string Lexer::CreateString(void)
{
	char prev_char = current_char;
	std::string result;
	
	while (!(current_char == '"' && prev_char != '\\') && current_char != (char)TokenType::END) {
		// try find a better fix for this?
		if (current_char == 'n' && prev_char == '\\') {
			// erase the \\ character appending
			result.erase(result.size() - 1);
			result += "\n";
		}
		else {
			result += current_char;
		}
		prev_char = current_char;
		Advance();
	}
	Advance();

	return result;
}

inline std::string Lexer::CreateIString(void)
{
	char prev_char = current_char;
	std::string result;

	while (!(current_char == '`' && prev_char != '\\') && current_char != (char)TokenType::END) {
		// try find a better fix for this?
		if (current_char == 'n' && prev_char == '\\') {
			// erase the \\ character appending
			result.erase(result.size() - 1);
			result += "\n";
		}
		else {
			result += current_char;
		}
		prev_char = current_char;
		Advance();
	}
	Advance();

	return result;
}

inline int Lexer::CreateInteger(std::string& from) {
	return stoi(from);
}

inline float Lexer::CreateFloat(std::string& from) {
	return stof(from);
}

inline void Lexer::SkipWhitespace(void) {
	while (isspace(current_char) && current_char != (char)TokenType::END) {
		Advance();
	}
}

inline void Lexer::SkipComment(void)
{
	char prev_char = current_char;

	while (current_char != '|' && prev_char != '\\') {
		prev_char = current_char;
		Advance();
	}
	Advance();
}

inline Token Lexer::ID(void) {
	std::string result = "";
	int lpos = 0;

	while ((isalnum(current_char) || current_char == '_') && current_char != (char)TokenType::END) {
		lpos++;
		result += current_char;
		Advance();
	}

	Token token = Token(result, TokenType::ID);

	try { token = RESERVED_KEYWORDS.at(result);}
	catch (std::out_of_range& e) {}

	return token;
}

Token Lexer::GetNextToken(void) {
	// while current_char is not end of code/file

	while (current_char != (char)TokenType::END) {
		// skip whitespaces
		if (isspace(current_char)) {
			SkipWhitespace();
			continue;
		}
		else if (isdigit(current_char)) {
			std::variant<int, float> number = CreateNumber();

			switch (number.index()) {
			case 0:
				// int
				return Token(std::get<0>(number), TokenType::INTEGER_LITERAL);
				break;
			case 1:
				// float
				return Token(std::get<1>(number), TokenType::FLOAT_LITERAL);
				break;
			}
		}
		else if (isalpha(current_char) || current_char == '_') {
			return ID();
		}
		else {
			switch (current_char) {
			case '=':
				if (Peek() == '=') {
					// create equals
					Advance();
					Advance();
					return Token('==', TokenType::EQUALS);
				}
				else {
					// create assign
					Advance();
					return Token('=', TokenType::ASSIGN);
				}
				break;
			case '<':
				if (Peek() == '=') {
					// leq
					Advance();
					Advance();
					return Token('<=', TokenType::LESSEQUALS);
				}
				else {
					Advance();
					return Token('<=', TokenType::LESS);
				}
				break;
			case '>':
				if (Peek() == '=') {
					// leq
					Advance();
					Advance();
					return Token('>=', TokenType::MOREEQUALS);
				}
				else {
					Advance();
					return Token('>=', TokenType::MORE);
				}
				break;
			case '!':
				if (Peek() == '=') {
					Advance();
					Advance();
					return Token('!=', TokenType::NOTEQUALS);
				}
				break;
			case '+':
			{
				Advance();
				switch (current_char) {
				case '=':
					Advance();
					return Token('+=', TokenType::PLUSEQ);
					break;

				case '+':
					Advance();
					return Token('++', TokenType::INCREMENT);
					break;
				
				default:
					return Token('+', TokenType::PLUS);
					break;
				}
				break;
			}
			case '-':
			{
				Advance();
				switch (current_char) {
				case '=':
					Advance();
					return Token('-=', TokenType::MINUSEQ);
					break;

				case '-':
					Advance();
					return Token('--', TokenType::DECREMENT);
					break;

				default:
					return Token('-', TokenType::MINUS);
					break;
				}
				break;
			}
			case '*':
			{
				Advance();
				if (current_char == '=') {
					Advance();
					return Token('*=', TokenType::MULTIPLYEQ);
				}
				else {
					return Token('*', TokenType::MULTIPLY);
				}
				break;
			}
			case '/':
			{
				Advance();
				if (current_char == '=') {
					Advance();
					return Token('/=', TokenType::DIVIDEEQ);
				}
				else {
					return Token('/', TokenType::DIVIDE);
				}
				break;
			}
			case '(':
				Advance();
				return Token('(', TokenType::LPAREN);
				break;
			case ')':
				Advance();
				return Token(')', TokenType::RPAREN);
				break;
			case ';':
				Advance();
				return Token(';', TokenType::SEMI);
				break;
			case '{':
				Advance();
				return Token('{', TokenType::LCURLY);
				break;
			case '}':
				Advance();
				return Token('}', TokenType::RCURLY);
				break;
			case ',':
				Advance();
				return Token(',', TokenType::COMMA);
				break;
			case ':':
				Advance();
				return Token(':', TokenType::COLON);
				break;
			case '"':
				Advance();
				return Token(CreateString(), TokenType::STRING_LITERAL);
				break;
			case '`':
				Advance();
				return Token(CreateIString(), TokenType::ISTRING_LITERAL);
				break;
			case '|':
				Advance();
				SkipComment();
				break;
			default:
				Advance();
				break;
			}
		}
	}

	return Token(1, TokenType::END);
}