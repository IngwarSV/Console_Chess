#include "Figure.h"





Figure::Figure()
{






}

Figure::~Figure()
{
}

const std::wstring& Figure::getType() const
{
	return _type;
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
