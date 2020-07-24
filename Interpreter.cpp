#include "Interpreter.h"

S1::POD S1::Interpreter::operator()(const S1::BINOP& visitee) {
	std::cout << "[WARNING] Visiting raw BINOP!" << std::endl;
	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::BINOP_ADD& visitee) {
	std::cout << "Left is: " << *visitee.left << std::endl;
	std::cout << "Right is: " << *visitee.right << std::endl;
	return std::visit(*this, *visitee.left) + std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const S1::BINOP_MIN& visitee) {
	return std::visit(*this, *visitee.left) - std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const S1::BINOP_MUL& visitee) {
	return std::visit(*this, *visitee.left) * std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const S1::BINOP_DIV& visitee) {
	return std::visit(*this, *visitee.left) / std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_EQ& visitee)
{
	return std::visit(*this, *visitee.left) == std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_LEQ& visitee)
{
	return std::visit(*this, *visitee.left) <= std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_NEQ& visitee)
{
	return std::visit(*this, *visitee.left) != std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_MEQ& visitee)
{
	return std::visit(*this, *visitee.left) >= std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_ME& visitee)
{
	return std::visit(*this, *visitee.left) > std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_LE& visitee)
{
	return std::visit(*this, *visitee.left) < std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_AND& visitee)
{
	return std::visit(*this, *visitee.left) && std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const BINOP_OR& visitee)
{
	return std::visit(*this, *visitee.left) || std::visit(*this, *visitee.right);
}

S1::POD S1::Interpreter::operator()(const S1::UNARYOP_ADD& visitee) {
	return 1 * std::visit(*this, *visitee.expr);
}

S1::POD S1::Interpreter::operator()(const S1::UNARYOP_MIN& visitee) {
	return -1 * std::visit(*this, *visitee.expr);
}

S1::POD S1::Interpreter::operator()(const S1::UNARYOP& visitee) {
	return POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::COMPOUND& visitee) {
	// we're going into a compound, increment our scope
	current_scope_level++;
	// and also create a new scope
	__AddScope();

	for (std::shared_ptr<S1::Node> child : visitee.children) {
		std::visit(*this, *child);
	}

	// exiting our compound, decrement scope
	current_scope_level--;

	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::ASSIGN& visitee) {
	std::string var_name = visitee.left->name;

	S1::POD data = std::visit(*this, *visitee.right);
	current_scope->memory.data[var_name] = data;

	return POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::VAR& visitee) {
	std::string var_name = visitee.name;
	try {
		__SearchSymbol(var_name.c_str());
	}
	catch (std::out_of_range) {
		// TODO: throw an S1 error
	}

	return __SearchMemory(var_name.c_str());
}

S1::POD S1::Interpreter::operator()(const S1::NOOP& visitee) {
	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::PROGRAM& visitee)
{
	for (std::shared_ptr<Node> node : visitee.block->children) {
		std::visit(*this, *node);
	}
	
	return POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::VARDECL& visitee)
{
	const char* type_name = std::get<std::string>(visitee.type->data).c_str();
	BuiltInTypeSymbol type_symbol = std::get<BuiltInTypeSymbol>(current_scope->symbols.Lookup(type_name));

	std::string var_name = visitee.var->name;
	VarSymbol var_symbol(var_name, type_symbol);

	current_scope->symbols.Define(var_symbol);

	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::TYPE& visitee)
{
	return POD(0);
}

S1::POD S1::Interpreter::operator()(const DISPLAY& visitee)
{
	S1::POD data = std::visit(*this, *visitee.to_display); // FIX: to_display has broken \n continue backtracking

	std::cout << PODToStr(data);

	return POD(0);
}

S1::POD S1::Interpreter::operator()(const RECEIVE& visitee)
{
	std::string data;
	std::cin.ignore();
	getline(std::cin, data);

	return data;
}

S1::POD S1::Interpreter::operator()(const FUNCDECL& visitee)
{
	// create function declaration in symbol table
	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const FUNCDEF& visitee)
{
	// create function definition in memory
	return POD(0);
}

S1::POD S1::Interpreter::operator()(const PARAM& visitee)
{
	return POD(0);
}

S1::POD S1::Interpreter::operator()(const IF& visitee)
{
	S1::POD data = std::visit(*this, *visitee.condition);

	if (data.index() == 4) {
		// if condition true
		if (std::get<bool>(data)) {
			return std::visit(*this, (S1::Node)*visitee.compound);
		}
		// otherwise visit the next else or else if
		else if (visitee.chained_if != nullptr) {
			return std::visit(*this, (S1::Node)*visitee.chained_if);
		}
	}

	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const ISTRING& visitee)
{
	std::string result = visitee.text;

	int last_pos = 0;

	for (std::shared_ptr<S1::Node> node : visitee.nodes) {
		int pos = result.find("$", last_pos);
		last_pos = pos + 1;

		if (pos != std::string::npos) {
			// quick bounds checking
			if (pos - 1 >= 0) {
				if (visitee.text[pos - 1] != '\\') {
					__Format(pos, result, node);
				}
			}
			else {
				__Format(pos, result, node);
			}
		}
	}

	return S1::POD(result);
}

void S1::Interpreter::__Format(int pos, std::string& text, std::shared_ptr<S1::Node> node)
{
	S1::POD data = std::visit(*this, *node);

	// TODO: better way?
	std::string substr = PODToStr(data);

	text = text.insert(pos, substr); // insert substr

	text = text.erase(pos + substr.length(), 1); // erase the $ char (hopefully)
}

void S1::Interpreter::__AddScope(void) {
	std::shared_ptr<Scope> new_scope = std::make_shared<Scope>(Scope());
	current_scope = new_scope;

	try {
		scopes.at(current_scope_level).emplace_back(new_scope); // checking if the level exists, and if so, just emplace a new scope
	}
	catch (std::out_of_range) {
		scopes[current_scope_level] = ScopeVector{new_scope}; // set current_scope_level to a new ScopeVector with a shared ptr to a scope;
	}
}

S1::Symbol S1::Interpreter::__SearchSymbol(const char* var_name)
{
	try {
		return current_scope->symbols.Lookup(var_name);
	}
	catch (S1::id_not_found) {
		int search_level = current_scope_level - 1;

		while (search_level != 0) {
			for (std::shared_ptr<Scope> scope_ptr : scopes[search_level]) {
				try {
					return scope_ptr->symbols.Lookup(var_name);
				}
				catch (S1::id_not_found) {}
			}

			search_level--;
		}

		throw new S1::id_not_found(var_name);
	}
}

S1::POD S1::Interpreter::__SearchMemory(const char* var_name)
{
	try {
		return current_scope->memory.Lookup(var_name);
	}
	catch (S1::id_not_found) {
		// iterate over all scopes
		int search_level = current_scope_level - 1;

		while (search_level != 0) {
			for (std::shared_ptr<Scope> scope_ptr : scopes[search_level]) {
				try {
					return scope_ptr->memory.Lookup(var_name);
				}
				catch (S1::id_not_found) {}
			}

			search_level--;
		}

		throw S1::id_not_found(var_name);
	}
}

void S1::Interpreter::PrintScopes(void) {
	for (std::pair<int, ScopeVector> element : scopes) {
		std::cout << "\n-----\nScope: " << element.first << std::endl;
		std::cout << element.second << std::endl;
	}
}

namespace S1 {
	std::ostream& S1::operator<<(std::ostream& os, const ScopeVector& scope_vec)
	{
		os << "[\n";
		for (std::shared_ptr<Scope> scope : scope_vec) {
			os << "    " << *scope << std::endl;
		}
		os << "]\n";

		return os;
	}

}