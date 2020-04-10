#pragma once

#include "Figure.h"

class F_King : public Figure {
public:
	F_King(Color color, Point location, Type type = Type::KING);
	~F_King();

	virtual void move() override;
};

class F_Queen : public Figure {
public:
	F_Queen(Color color, Point location, Type type = Type::QUEEN);
	~F_Queen();

	virtual void move() override;
};

class F_Bishop : public Figure {
public:
	F_Bishop(Color color, Point location, Type type = Type::BISHOP);
	~F_Bishop();

	virtual void move() override;
};

class F_Knight : public Figure {
public:
	F_Knight(Color color, Point location, Type type = Type::KNIGHT);
	~F_Knight();

	virtual void move() override;
};

class F_Rook : public Figure {
public:
	F_Rook(Color color, Point location, Type type = Type::ROOK);
	~F_Rook();

	virtual void move() override;
};

class F_Pawn : public Figure {
public:
	F_Pawn(Color color, Point location, Type type = Type::PAWN);
	~F_Pawn();

	virtual void move() override;
};


