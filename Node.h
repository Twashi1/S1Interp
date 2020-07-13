#pragma once

#include <memory>
#include <variant>
#include <iostream>
#include <vector>

#include "Token.h"

namespace S1 {
	struct BINOP;
	struct ASSIGN;
	struct UNARYOP;
	struct COMPOUND;
	struct NOOP;
	struct VAR;

	struct BINOP_ADD;
	struct BINOP_MIN;
	struct BINOP_MUL;
	struct BINOP_DIV;

	struct UNARYOP_ADD;
	struct UNARYOP_MIN;

	typedef std::variant<
		// POD
		int,
		float,
		double,
		bool,
		// BINOP
		BINOP,
		BINOP_ADD,
		BINOP_MIN,
		BINOP_MUL,
		BINOP_DIV,
		// UNARYOP
		UNARYOP,
		UNARYOP_ADD,
		UNARYOP_MIN,
		// OTHER
		COMPOUND,
		ASSIGN,
		NOOP,
		VAR
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

	/* BINOP Children */
	struct BINOP_ADD : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_MIN : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_MUL : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };
	struct BINOP_DIV : public BINOP { using BINOP::BINOP; using BINOP::left; using BINOP::right; };

	struct UNARYOP {
		std::shared_ptr<Node> expr;

		UNARYOP() : expr(nullptr) {};
		UNARYOP(const UNARYOP& copy);
		UNARYOP(const Node& expr);

		virtual ~UNARYOP() {}

		friend std::ostream& operator<<(std::ostream& os, const UNARYOP& unaryop);
	};

	/* UNARYOP Children */

	struct UNARYOP_ADD : public UNARYOP { using UNARYOP::UNARYOP; using UNARYOP::expr; };
	struct UNARYOP_MIN : public UNARYOP { using UNARYOP::UNARYOP; using UNARYOP::expr; };

	struct COMPOUND {
		std::vector<std::shared_ptr<Node>> children;

		COMPOUND(const COMPOUND& copy);
		COMPOUND(const std::vector<Node>& nodes);
		COMPOUND(const std::vector<std::shared_ptr<Node>>& nodes);
	};

	struct VAR {
		Token token; // check if the whole token is needed later
		std::string name;

		VAR(const VAR& copy) : token(copy.token), name(copy.name) {}
		VAR(const Token& token) : token(token), name(std::get<std::string>(token.data)) {}

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
}