#include "NodeVisitor.h"

S1::POD S1::Visitor::operator()(const S1::BINOP& visitee) {
	std::cout << "[WARNING] Visiting raw BINOP!" << std::endl;
	return S1::POD(0);
}

S1::POD S1::Visitor::operator()(const S1::BINOP_ADD& visitee) {
	Info("Visiting BINOP_ADD");
	std::cout << "Left is: " << *visitee.left << std::endl;
	std::cout << "Right is: " << *visitee.right << std::endl;
	return std::visit(*this, *visitee.left) + std::visit(*this, *visitee.right);
}

S1::POD S1::Visitor::operator()(const S1::BINOP_MIN& visitee) {
	Info("Visiting BINOP_MIN");
	return std::visit(*this, *visitee.left) - std::visit(*this, *visitee.right);
}

S1::POD S1::Visitor::operator()(const S1::BINOP_MUL& visitee) {
	Info("Visiting BINOP_MUL");
	return std::visit(*this, *visitee.left) * std::visit(*this, *visitee.right);
}

S1::POD S1::Visitor::operator()(const S1::BINOP_DIV& visitee) {
	Info("Visiting BINOP_DIV");
	return std::visit(*this, *visitee.left) / std::visit(*this, *visitee.right);
}

S1::POD S1::Visitor::operator()(const S1::UNARYOP_ADD& visitee) {
	Info("Visiting UNARYOP_ADD");
	std::cout << "UNARYOP_ADD is: " << std::get<int>(std::visit(*this, *visitee.expr)) << std::endl;
	return 1 * std::visit(*this, *visitee.expr);
}

S1::POD S1::Visitor::operator()(const S1::UNARYOP_MIN& visitee) {
	Info("Visiting UNARYOP_MIN");
	std::cout << "UNARYOP_MIN is: " << std::get<int>(std::visit(*this, *visitee.expr)) << std::endl;
	return -1 * std::visit(*this, *visitee.expr);
}

S1::POD S1::Visitor::operator()(const S1::UNARYOP& visitee) {
	std::cout << "[WARNING] Visiting raw UNARYOP!" << std::endl;
	return POD(0);
}

S1::POD S1::Visitor::operator()(const S1::COMPOUND& visitee) {
	Info("Visiting COMPOUND");
	for (std::shared_ptr<S1::Node> child : visitee.children) {
		std::cout << "Visiting COMPOUND child..." << std::endl;
		std::visit(*this, *child);
	}

	return S1::POD(0);
}

S1::POD S1::Visitor::operator()(const S1::ASSIGN& visitee) {
	Info("Visiting ASSIGN");
	std::string var_name = visitee.left->name;

	S1::POD val = std::visit(*this, *visitee.right);

	std::cout << "Visit returns: " << val << ", as int: " << std::get<int>(val) << std::endl;

	GLOBAL_SCOPE[var_name] = val;

	return S1::POD(0);
}

S1::POD S1::Visitor::operator()(const VAR& visitee) {
	Info("Visiting VAR");
	std::string var_name = visitee.name;

	try {
		std::cout << "Loading variable!" << std::endl;
		S1::POD value = GLOBAL_SCOPE.at(var_name);
		return value;

	} catch (std::out_of_range) {
		Error("[S1::Visitor](VAR) Variable did not exist!");
		return S1::POD(0);
	}
}

S1::POD S1::Visitor::operator()(const S1::NOOP& visitee) {
	Info("Visiting NOOP");
	return S1::POD(0);
}

S1::POD S1::operator+(const POD& left, const POD& right) {
	// this works because there are less than 10 variants in left
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) + std::get<0>(right); break;
	case 01: return std::get<0>(left) + std::get<1>(right); break;
	case 02: return std::get<0>(left) + std::get<2>(right); break;
	case 03: return std::get<0>(left) + std::get<3>(right); break;
	case 10: return std::get<1>(left) + std::get<0>(right); break;
	case 11: return std::get<1>(left) + std::get<1>(right); break;
	case 12: return std::get<1>(left) + std::get<2>(right); break;
	case 13: return std::get<1>(left) + std::get<3>(right); break;
	case 20: return std::get<2>(left) + std::get<0>(right); break;
	case 21: return std::get<2>(left) + std::get<1>(right); break;
	case 22: return std::get<2>(left) + std::get<2>(right); break;
	case 23: return std::get<2>(left) + std::get<3>(right); break;
	case 30: return std::get<3>(left) + std::get<0>(right); break;
	case 31: return std::get<3>(left) + std::get<1>(right); break;
	case 32: return std::get<3>(left) + std::get<2>(right); break;
	case 33: return std::get<3>(left) + std::get<3>(right); break;
	}
}

S1::POD S1::operator-(const POD& left, const POD& right) {
	// this works because there are less than 10 variants in left
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) - std::get<0>(right); break;
	case 01: return std::get<0>(left) - std::get<1>(right); break;
	case 02: return std::get<0>(left) - std::get<2>(right); break;
	case 03: return std::get<0>(left) - std::get<3>(right); break;
	case 10: return std::get<1>(left) - std::get<0>(right); break;
	case 11: return std::get<1>(left) - std::get<1>(right); break;
	case 12: return std::get<1>(left) - std::get<2>(right); break;
	case 13: return std::get<1>(left) - std::get<3>(right); break;
	case 20: return std::get<2>(left) - std::get<0>(right); break;
	case 21: return std::get<2>(left) - std::get<1>(right); break;
	case 22: return std::get<2>(left) - std::get<2>(right); break;
	case 23: return std::get<2>(left) - std::get<3>(right); break;
	case 30: return std::get<3>(left) - std::get<0>(right); break;
	case 31: return std::get<3>(left) - std::get<1>(right); break;
	case 32: return std::get<3>(left) - std::get<2>(right); break;
	case 33: return std::get<3>(left) - std::get<3>(right); break;
	}
}

S1::POD S1::operator*(const POD& left, const POD& right) {
	// this works because there are less than 10 variants in left
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) * std::get<0>(right); break;
	case 01: return std::get<0>(left) * std::get<1>(right); break;
	case 02: return std::get<0>(left) * std::get<2>(right); break;
	case 03: return std::get<0>(left) * std::get<3>(right); break;
	case 10: return std::get<1>(left) * std::get<0>(right); break;
	case 11: return std::get<1>(left) * std::get<1>(right); break;
	case 12: return std::get<1>(left) * std::get<2>(right); break;
	case 13: return std::get<1>(left) * std::get<3>(right); break;
	case 20: return std::get<2>(left) * std::get<0>(right); break;
	case 21: return std::get<2>(left) * std::get<1>(right); break;
	case 22: return std::get<2>(left) * std::get<2>(right); break;
	case 23: return std::get<2>(left) * std::get<3>(right); break;
	case 30: return std::get<3>(left) * std::get<0>(right); break;
	case 31: return std::get<3>(left) * std::get<1>(right); break;
	case 32: return std::get<3>(left) * std::get<2>(right); break;
	case 33: return std::get<3>(left) * std::get<3>(right); break;
	}
}

S1::POD S1::operator/(const POD& left, const POD& right) {
	// this works because there are less than 10 variants in left
	switch (left.index() * 10 + right.index()) {
	case 00: return std::get<0>(left) / std::get<0>(right); break;
	case 01: return std::get<0>(left) / std::get<1>(right); break;
	case 02: return std::get<0>(left) / std::get<2>(right); break;
	case 03: return std::get<0>(left) / std::get<3>(right); break;
	case 10: return std::get<1>(left) / std::get<0>(right); break;
	case 11: return std::get<1>(left) / std::get<1>(right); break;
	case 12: return std::get<1>(left) / std::get<2>(right); break;
	case 13: return std::get<1>(left) / std::get<3>(right); break;
	case 20: return std::get<2>(left) / std::get<0>(right); break;
	case 21: return std::get<2>(left) / std::get<1>(right); break;
	case 22: return std::get<2>(left) / std::get<2>(right); break;
	case 23: return std::get<2>(left) / std::get<3>(right); break;
	case 30: return std::get<3>(left) / std::get<0>(right); break;
	case 31: return std::get<3>(left) / std::get<1>(right); break;
	case 32: return std::get<3>(left) / std::get<2>(right); break;
	case 33: return std::get<3>(left) / std::get<3>(right); break;
	}
}

namespace S1 {
	std::ostream& operator<<(std::ostream& os, const POD& num) {
		os << "POD(" << num.index() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const std::map<std::string, S1::POD> table)
	{
		os << "{" << std::endl;
		for (const std::pair<std::string, S1::POD>& pair : table) {
			os << "    {" << pair.first << ": " << pair.second << "}" << std::endl;
		}
		os << "}";

		return os;
	}
}