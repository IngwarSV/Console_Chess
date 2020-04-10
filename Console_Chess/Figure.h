#pragma once
#include <string>
#include "Specification.h"

class Figure
{
private:
	Color _color;
	Type _type;
	std::wstring _name;
	Point _location;

public:
	Figure(Color color, Point location, Type type);
	virtual ~Figure();

	//bool _whiteSide;
	bool _firstMove;

	virtual void move() = 0;

	const Color getColor() const;
	const std::wstring& getFigureName() const;
	const Point getLocation() const;

	void setLocation(int x, int y);
};
