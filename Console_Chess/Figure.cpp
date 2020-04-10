#include "Figure.h"





Figure::Figure(Color color, Point location, Type type)
{
	this->_color = color;
	this->_type = type;
	this->_name += color;
	this->_name += static_cast<wchar_t>(type);
	this->_location = location;
	
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

const std::wstring& Figure::getFigureName() const
{
	return _name;
}

const Point Figure::getLocation() const
{
	return _location;
}

void Figure::setLocation(int x, int y)
{
	_location.x = x;
	_location.y = y;
}
