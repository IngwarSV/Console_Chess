#pragma once
#include <string>
#include <vector>

#include "Specification.h"

class Figure
{
protected:
	Color _color;
	Type _type;
	std::wstring _name;
	Point _location;
	std::vector<Point>* _possibleMoves = nullptr;

public:
	Figure(Color color, Point location, Type type);
	virtual ~Figure();

	// attributes
	



	//bool _whiteSide;
	bool _firstMove;

	virtual std::vector<Point>* getPossibleMoves(Figure*** board) = 0;

	//virtual void checkMove(const Figure*** board);

	const Color getColor() const;
	const Type getType() const;
	const std::wstring& getFigureName() const;
	const Point getLocation() const;
	//const std::vector<Point>* getPossibleMoves() const;


	void setLocation(Point point);
};
