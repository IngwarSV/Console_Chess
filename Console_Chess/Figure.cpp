#include "Figure.h"





Figure::Figure(Color color, Point location, Type type)
{
	this->_color = color;
	this->_type = type;
	this->_name += static_cast<wchar_t>(color);
	this->_name += static_cast<wchar_t>(type);
	this->_location = location;

	this->_possibleMoves = new std::vector<Point>();

	_firstMove = true;
	
	/*if (_color == WHITE) {
		_whiteSide = true;
	}
	else {
		_whiteSide = false;
	}*/
	
}

Figure::~Figure()
{
}

const Color Figure::getColor() const
{
	return _color;
}

const Type Figure::getType() const
{
	return _type;
}

const std::wstring& Figure::getFigureName() const
{
	return _name;
}

const Point Figure::getLocation() const
{
	return _location;
}

void Figure::setLocation(Point point)
{
	
	_location.x = point.x;
	_location.y = point.y;
}
