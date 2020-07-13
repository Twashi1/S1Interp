#pragma once

#include "NodeVisitor.h"
#include "Parser.h"

class Interpreter : public S1::Visitor {
public:
	Parser* parser;

	Interpreter(Parser* parser) : parser(parser) {}
	virtual ~Interpreter() {}

	S1::POD Interpret() {
		S1::Node tree_start = parser->Parse();
		std::cout << "Tree starts as: " << tree_start << std::endl;
		return S1::POD(std::visit(*this, tree_start));
	}
};