#pragma once

#include "Specification.h"
#include "Figure.h"

using namespace DEF_SETT;

// each figure-heir overrides getPossibleMoves method

class F_King : public Figure {
public:
	F_King(Color color, Point location, Type type = Type::KING);
	virtual ~F_King();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;
};


class F_Queen : public Figure {
public:
	F_Queen(Color color, Point location, Type type = Type::QUEEN);
	virtual ~F_Queen();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;
};


class F_Bishop : public Figure {
public:
	F_Bishop(Color color, Point location, Type type = Type::BISHOP);
	virtual ~F_Bishop();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;
};


class F_Knight : public Figure {
public:
	F_Knight(Color color, Point location, Type type = Type::KNIGHT);
	virtual ~F_Knight();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;
};


class F_Rook : public Figure {
public:
	F_Rook(Color color, Point location, Type type = Type::ROOK);
	virtual ~F_Rook();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;

};


class F_Pawn : public Figure {
public:
	F_Pawn(Color color, Point location, Type type = Type::PAWN);
	virtual ~F_Pawn();

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) override;
};


