#pragma once
#include <string>
#include <vector>

#include "Specification.h"

class Figure
{
protected:
	Color _color;
	Type _type;
	std::wstring _name{};
	Point _location;

	std::vector<Point>* _possibleMoves = nullptr;

public:
	Figure(Color color, Point location, Type type);
	virtual ~Figure();

	// attributes
	bool _firstMove;

	// methods

	// pure virtual method, returns vector of figure's possible moves, 
	// considering situation on the board
	virtual std::vector<Point>* getPossibleMoves(Figure*** board) = 0;

	////getters
	const Color getColor() const;
	const Type getType() const;
	const std::wstring& getFigureName() const;
	const Point getLocation() const;
	
	////setters
	void setLocation(Point point);
};
