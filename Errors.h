#pragma once

#include <exception>
#include <sstream>

#include "Token.h"

namespace S1 {
	struct unexpected_token : public std::exception {
		Token token;
		TokenType expected_type;
		int line_num;
		int column_num;

		unexpected_token(const Token& token, const TokenType& expected_type, int line_num, int column_num) : token(token), expected_type(expected_type), line_num(line_num), column_num(column_num) {}

		const char* what() const throw () {
			std::stringstream message;

			message
				<< "[Syntax Error] Unexpected token: " << token << " at "
				<< line_num << ":" << column_num
				<< ", expected: " << expected_type;

			return message.str().c_str();
		}
	};

	struct id_not_found : public std::exception {
		std::string id_name;

		id_not_found(const std::string& id_name) : id_name(id_name) {}
		id_not_found(const char* id_name) : id_name(id_name) {}

		const char* what() const throw () {
			std::stringstream message;

			message
				<< "[Semantic Error] Identifier not found: " << id_name;

			return message.str().c_str();
		}
	};
}