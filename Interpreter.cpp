#include "Interpreter.h"

S1::POD S1::Interpreter::operator()(const S1::BINOP_ADD& visitee) {
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

S1::POD S1::Interpreter::operator()(const UNSCOPED_COMPOUND& visitee)
{
	for (std::shared_ptr<S1::Node> child : visitee.children) {
		std::visit(*this, *child);
	}

	return POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::COMPOUND& visitee) {
	// we're going into a compound, increment our scope
	current_scope_level++;
	// and also create a new scope
	__AddScope();

	for (std::shared_ptr<S1::Node> child : visitee.children) {
		// index of RETURN
		try {
			std::get<RETURN>(*child);
			S1::POD data = std::visit(*this, *child);
			current_scope_level--;
			return data;
		}
		catch (std::bad_variant_access) {
			std::visit(*this, *child);
		}
	}

	// exiting our compound, decrement scope
	current_scope_level--;

	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::ASSIGN& visitee) {
	std::string var_name = visitee.left->name;

	S1::POD data = std::visit(*this, *visitee.right);
	current_scope->memory.Define(var_name, data);

	return POD(0);
}

S1::POD S1::Interpreter::operator()(const S1::VAR& visitee) {
	std::string var_name = visitee.name;
	__SearchSymbol(var_name.c_str());

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
	current_scope->memory.Define(visitee.name, visitee);
	return S1::POD(0);
}

S1::POD S1::Interpreter::operator()(const FUNCCALL& visitee)
{
	// get the definition of the function
	S1::FUNCDEF func_def = std::get<S1::FUNCDEF>(std::get<S1::Node>(__SearchMemory(visitee.name.c_str())));

	// get the parameters
	for (int i = 0; i < visitee.params.size(); i++) {
		S1::Node data = *visitee.params[i];
		S1::PARAM argument_param = *func_def.params[i];

		// add declarations for each parameter inside the function compound, and assign them to data
		// create the declaration
		S1::Node declaration = VARDECL(argument_param.var, argument_param.type);
		S1::Node assign = ASSIGN(*argument_param.var, data);

		// add both to compound
		func_def.compound->children.insert(func_def.compound->children.begin(), std::make_shared<S1::Node>(declaration));
		func_def.compound->children.insert(func_def.compound->children.begin(), std::make_shared<S1::Node>(assign));
	}

	// now visit the function
	return std::visit(*this, (S1::Node)*func_def.compound);;
}

S1::POD S1::Interpreter::operator()(const RETURN& visitee)
{
	return std::visit(*this, *visitee.data);
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

S1::POD S1::Interpreter::operator()(const WHILE& visitee)
{
	S1::POD data = std::visit(*this, *visitee.condition);

	if (data.index() == 4) {
		while (std::get<bool>(data)) {
			for (std::shared_ptr<S1::Node> node : visitee.compound->children) {
				std::visit(*this, *node);
			}

			data = std::visit(*this, *visitee.condition);
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
	catch (std::out_of_range) {
		int search_level = current_scope_level - 1;

		while (search_level >= 0) {
			for (std::shared_ptr<Scope> scope_ptr : scopes[search_level]) {
				try {
					return scope_ptr->symbols.Lookup(var_name);
				}
				catch (std::out_of_range) {}
			}

			search_level--;
		}

		std::cout << "Error, couldn't find symbol of name: " << var_name << std::endl;
		PrintScopes();
	}
}

S1::POD S1::Interpreter::__SearchMemory(const char* var_name)
{
	try {
		return current_scope->memory.Lookup(var_name);
	}
	catch (std::out_of_range) {
		// iterate over all scopes
		int search_level = current_scope_level - 1;

		while (search_level >= 0) {
			for (std::shared_ptr<Scope> scope_ptr : scopes[search_level]) {
				try {
					return scope_ptr->memory.Lookup(var_name);
				}
				catch (std::out_of_range) {}
			}

			search_level--;
		}

		std::cout << "Error, couldn't find memory of name: " << var_name << std::endl;
		PrintScopes();
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