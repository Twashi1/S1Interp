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
	children.reserve(nodes.size() * sizeof(std::shared_ptr<S1::Node>));

	for (const S1::Node& node : nodes) {
		children.emplace_back(std::make_shared<S1::Node>(node));
	}
}

S1::COMPOUND::COMPOUND(const std::vector<std::shared_ptr<S1::Node>>& nodes) {
	children.reserve(nodes.size() * sizeof(std::shared_ptr<S1::Node>));

	for (const std::shared_ptr<S1::Node> node : nodes) {
		children.emplace_back(node);
	}
}

S1::FUNCDECL::FUNCDECL(const std::string& name, const TYPE& type, const std::vector<PARAM>& params) : name(name), type(std::make_shared<TYPE>(type)) {
	this->params.reserve(params.size() * sizeof(std::shared_ptr<PARAM>));

	for (const PARAM& param : params) {
		this->params.emplace_back(std::make_shared<PARAM>(param));
	}
}

S1::FUNCDEF::FUNCDEF(const std::string& name, const TYPE& type, const S1::COMPOUND& compound, const std::vector<PARAM>& params)
	: name(name), type(std::make_shared<TYPE>(type)), compound(std::make_shared<COMPOUND>(compound))
{
	this->params.reserve(params.size() * sizeof(std::shared_ptr<PARAM>));

	for (const PARAM& param : params) {
		this->params.emplace_back(std::make_shared<PARAM>(param));
	}
}

S1::ISTRING::ISTRING(const std::string& text, const std::vector<Node>& nodes) : text(text) {
	this->nodes.reserve(sizeof(std::shared_ptr<Node>) * nodes.size());

	for (Node node : nodes) {
		this->nodes.emplace_back(std::make_shared<Node>(node));
	}
}

S1::FUNCCALL::FUNCCALL(const std::string& name, const std::vector<S1::Node>& params)
	: name(name)
{
	this->params.reserve(sizeof(std::shared_ptr<S1::Node>) * params.size());

	for (S1::Node param : params) {
		this->params.emplace_back(std::make_shared<S1::Node>(param));
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

	std::ostream& operator<<(std::ostream& os, const ISTRING& istring) {
		os << "ISTRING(" << istring.text << ")";
		return os;
	}
}