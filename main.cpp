#include <string>
#include <iostream>
#include <fstream>

#include "Interpreter.h"

std::ostream& operator<<(std::ostream& os, const S1::POD& num) {
	os << "POD(" << num.index() << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<std::string, S1::POD> table)
{
	os << "{" << std::endl;
	for (const std::pair<std::string, S1::POD>& pair : table) {
		os << "    {" << pair.first << ": " << std::get<int>(pair.second) << "}" << std::endl;
	}
	os << "}";

	return os;
}

int main(void) {
	std::cout << "S1 Interpreter launching!" << std::endl;
	std::string script_text;
	std::ifstream script("test.s1", std::ios::in);

	if (script) {
		script_text = std::string((std::istreambuf_iterator<char>(script)), std::istreambuf_iterator<char>());
	}

	Lexer s1_lexer(script_text);
	Parser s1_parser(&s1_lexer);
	Interpreter s1_interpreter(&s1_parser);

	S1::POD output = s1_interpreter.Interpret();

	std::cout << s1_interpreter.GLOBAL_SCOPE << std::endl;
}