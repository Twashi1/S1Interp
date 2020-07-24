#pragma once

#include <memory>
#include <variant>
#include <iostream>
#include <vector>

#include "Token.h"

namespace S1 {
	struct BINOP;
	struct BINOP_ADD;
	struct BINOP_MIN;
	struct BINOP_MUL;
	struct BINOP_DIV;

	struct UNARYOP;
	struct UNARYOP_ADD;
	struct UNARYOP_MIN;

	struct COMPOUND;
	struct PROGRAM;

	struct ASSIGN;
	struct NOOP;

	struct VAR;
	struct TYPE;
	struct VARDECL;
	struct PARAM;

	struct DISPLAY;
	struct RECEIVE;

	struct FUNCDECL;
	struct FUNCDEF;
	struct FUNCCALL;

	struct ISTRING;

	struct BINOP_EQ;
	struct BINOP_NEQ;
	struct BINOP_LE;
	struct BINOP_ME;
	struct BINOP_LEQ;
	struct BINOP_MEQ;
	struct BINOP_AND;
	struct BINOP_OR;

	struct IF;

	typedef std::variant<
		// POD
		int,
		float,
		double,
		bool,
		std::string,
		ISTRING,
		// BINOP
		BINOP,
		BINOP_ADD,
		BINOP_MIN,
		BINOP_MUL,
		BINOP_DIV,
		BINOP_EQ,
		BINOP_NEQ,
		BINOP_LE,
		BINOP_ME,
		BINOP_LEQ,
		BINOP_MEQ,
		BINOP_AND,
		BINOP_OR,
		// UNARYOP
		UNARYOP,
		UNARYOP_ADD,
		UNARYOP_MIN,
		// CONSTRUCTS
		COMPOUND,
		PROGRAM,
		NOOP,
		// OTHER
		VAR,
		TYPE,
		VARDECL,
		ASSIGN, // VARDEF
		FUNCDECL,
		FUNCDEF,
		PARAM,
		IF,
		// BUILT-IN TEMP
		DISPLAY,
		RECEIVE
	> Node;

	struct BINOP {
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;

		BINOP() : left(nullptr), right(nullptr) {};
		BINOP(const BINOP& copy);
		BINOP(const Node& left, const Node& right);

		virtual ~BINOP() {}

		friend std::ostream& operator<<(std::ostream& os, const BINOP& binop);
	};

	// BINOP CHILDREN

	struct BINOP_ADD : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_MIN : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_MUL : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_DIV : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };

	struct BINOP_EQ : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_LEQ : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_MEQ : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_NEQ : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_LE : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_ME : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };

	struct BINOP_AND : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_OR : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };

	struct UNARYOP {
		std::shared_ptr<Node> expr;

		UNARYOP() : expr(nullptr) {};
		UNARYOP(const UNARYOP& copy);
		UNARYOP(const Node& expr);

		virtual ~UNARYOP() {}

		friend std::ostream& operator<<(std::ostream& os, const UNARYOP& unaryop);
	};

	// UNARYOP CHILDREN

	struct UNARYOP_ADD : public UNARYOP { using UNARYOP::UNARYOP; using UNARYOP::expr; };
	struct UNARYOP_MIN : public UNARYOP { using UNARYOP::UNARYOP; using UNARYOP::expr; };

	struct COMPOUND {
		std::vector<std::shared_ptr<Node>> children;

		COMPOUND(const COMPOUND& copy);
		COMPOUND(const std::vector<Node>& nodes);
		COMPOUND(const std::vector<std::shared_ptr<Node>>& nodes);
	};

	struct VAR {
		Token token;
		std::string name;

		VAR(const VAR& copy) : token(copy.token), name(copy.name) {}
		VAR(const Token& token) : token(token) {
			try { name = std::get<std::string>(token.data); }
			catch (std::bad_variant_access) {
				std::cout << "[NODE ERROR]: While creating variable: expected string but got: " << token.data.index() << std::endl;
				name = "err";
			}
		}

		virtual ~VAR() {}

		friend std::ostream& operator<<(std::ostream& os, const VAR& var);
	};

	struct ASSIGN {
		std::shared_ptr<VAR> left;
		std::shared_ptr<Node> right;

		ASSIGN(const ASSIGN& copy) : left(copy.left), right(copy.right) {}
		ASSIGN(const VAR& left, const Node& right) : left(std::make_shared<S1::VAR>(left)), right(std::make_shared<S1::Node>(right)) {}
	};

	struct NOOP {};

	struct TYPE {
		Token token;
		TokenData data;

		TYPE(const TYPE& copy) : token(copy.token), data(copy.data) {}
		TYPE(const Token& token) : token(token), data(token.data) {}
	};

	struct VARDECL {
		std::shared_ptr<VAR> var;
		std::shared_ptr<TYPE> type;

		VARDECL(const VARDECL& decl) : var(decl.var), type(decl.type) {}
		VARDECL(const VAR& var, const TYPE& type) : var(std::make_shared<VAR>(var)), type(std::make_shared<TYPE>(type)) {}
		VARDECL(const std::shared_ptr<VAR> var, const std::shared_ptr<TYPE> type) : var(var), type(type) {}
	};

	struct PROGRAM {
		std::string name;
		std::shared_ptr<COMPOUND> block;

		PROGRAM(const PROGRAM& copy) : name(copy.name), block(copy.block) {}
		PROGRAM(const std::string& name, const COMPOUND& block) : name(name), block(std::make_shared<COMPOUND>(block)) {}
	};

	struct DISPLAY {
		std::shared_ptr<Node> to_display;

		DISPLAY(const DISPLAY& copy) : to_display(copy.to_display) {}
		DISPLAY(const Node& to_display) : to_display(std::make_shared<Node>(to_display)) {}
		DISPLAY(const std::shared_ptr<Node>& to_display) : to_display(to_display) {}
	};

	struct RECEIVE {};

	struct ISTRING {
		std::string text;
		std::vector<std::shared_ptr<Node>> nodes;

		ISTRING(const ISTRING& copy) : text(copy.text), nodes(copy.nodes) {}
		ISTRING(const std::string& text, const std::vector<Node>& nodes);
		ISTRING(const std::string& text, const std::vector<std::shared_ptr<Node>>& nodes) : text(text), nodes(nodes) {}

		friend std::ostream& operator<<(std::ostream& os, const ISTRING& istring);
	};

	struct PARAM {
		std::shared_ptr<VAR> var;
		std::shared_ptr<TYPE> type;

		PARAM(const PARAM& copy) : var(copy.var), type(copy.type) {}
		PARAM(const VAR& var, const TYPE& type) : var(std::make_shared<VAR>(var)), type(std::make_shared<TYPE>(type)) {}
	};

	struct FUNCDECL {
		std::string name;
		std::shared_ptr<TYPE> type; // return type

		std::vector<std::shared_ptr<PARAM>> params;

		FUNCDECL(const FUNCDECL& copy) : name(copy.name), type(copy.type), params(copy.params) {}

		FUNCDECL(const std::string& name, const TYPE& type, const std::vector<PARAM>& params);

		FUNCDECL(const std::string& name, const TYPE& type, const std::vector<std::shared_ptr<PARAM>>& params)
			: name(name), type(std::make_shared<TYPE>(type)), params(params)
		{}
	};

	struct FUNCDEF {
		std::string name;
		std::shared_ptr<TYPE> type; // return type

		std::vector<std::shared_ptr<PARAM>> params;
		std::shared_ptr<S1::COMPOUND> compound;

		FUNCDEF(const FUNCDEF& copy) : name(copy.name), type(copy.type), params(copy.params), compound(copy.compound) {}

		FUNCDEF(const std::string& name, const TYPE& type, const S1::COMPOUND& compound, const std::vector<PARAM>& params);

		FUNCDEF(const std::string& name, const TYPE& type, const S1::COMPOUND& compound, const std::vector<std::shared_ptr<PARAM>>& params)
			: name(name), type(std::make_shared<TYPE>(type)), params(params), compound(std::make_shared<COMPOUND>(compound))
		{}

		FUNCDEF(const FUNCDECL& copy, const S1::COMPOUND& compound) : name(copy.name), type(copy.type), params(copy.params), compound(std::make_shared<S1::COMPOUND>(compound)) {}
	};

	struct IF {
		std::shared_ptr<S1::Node> condition;
		std::shared_ptr<S1::COMPOUND> compound;
		std::shared_ptr<S1::IF> chained_if = nullptr;

		IF(const IF& copy) : condition(copy.condition), compound(copy.compound), chained_if(copy.chained_if) {}
		IF(const S1::Node& condition, const S1::COMPOUND& compound, const std::shared_ptr<S1::IF> chained_if = nullptr)
			: condition(std::make_shared<S1::Node>(condition)), compound(std::make_shared<COMPOUND>(compound)), chained_if(chained_if)
		{}
	};
}