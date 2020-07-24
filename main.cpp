#include <string>
#include <iostream>
#include <fstream>

#include "Interpreter.h"

namespace S1 {
	std::string divider = "----------------------\n";

	void Run(const char* path) {
		// Getting data from script
		std::string script_text;
		std::ifstream script(path, std::ios::in);

		if (script) {
			script_text = std::string((std::istreambuf_iterator<char>(script)), std::istreambuf_iterator<char>());
		}

		// init lexer, parser, and interpreter
		Lexer lexer(script_text);
		Parser parser(&lexer);
		S1::Interpreter s1_interpreter(&parser);

		// call interpret
		std::cout << "S1 Interpreter launching!" << std::endl;
		s1_interpreter.Interpret();

		s1_interpreter.PrintScopes();
	}
}

int main(int argc, char* argv[]) {
	if (argc >= 2) {
		S1::Run(argv[1]);
	}
	else {
		S1::Run("scripts/test.s1");
	}

	system("pause");

	return 0;
}