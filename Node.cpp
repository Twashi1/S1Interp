#include "Node.h"

S1::BINOP::BINOP(const S1::Node& left, const  S1::Node& right) {
	this->left = std::make_shared<Node>(left);
	this->right = std::make_shared<Node>(right);
}

S1::BINOP::BINOP(const S1::BINOP& copy) {
	left = copy.left;
	right = copy.right;
}

S1::UNARYOP::UNARYOP(const S1::Node& expr) {
	this->expr = std::make_shared<S1::Node>(expr);
}

S1::UNARYOP::UNARYOP(const  S1::UNARYOP& copy) {
	expr = copy.expr;
}

S1::COMPOUND::COMPOUND(const S1::COMPOUND& copy)
{
	children = copy.children;
}

S1::COMPOUND::COMPOUND(const std::vector<S1::Node>& nodes) {
	std::cout << "Constructing Compound from nodes" << std::endl;

	children.reserve(nodes.size() * sizeof(std::shared_ptr<S1::Node>));

	std::cout << "Nodes has size: " << nodes.size() << std::endl;

	for (const S1::Node node : nodes) {
		children.emplace_back(std::make_shared<S1::Node>(node));
	}
}

S1::COMPOUND::COMPOUND(const std::vector<std::shared_ptr<S1::Node>>& nodes) {
	std::cout << "Constructing Compound from nodes" << std::endl;

	children.reserve(nodes.size() * sizeof(std::shared_ptr<S1::Node>));

	std::cout << "Nodes has size: " << nodes.size() << std::endl;

	for (const std::shared_ptr<S1::Node> node : nodes) {
		children.emplace_back(node);
	}
}

namespace S1 {
	std::ostream& operator<<(std::ostream& os, const Node& node) {
		os << "Node(" << node.index() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const  S1::BINOP& binop) {
		os << "BINOP(" << *binop.left << ", " << *binop.right << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const S1::UNARYOP& unaryop) {
		os << "UNARYOP(" << *unaryop.expr << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const VAR& var) {
		os << "VAR(" << var.name << ")";
		return os;
	}
}