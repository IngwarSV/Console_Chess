#pragma once
#include <string>
#include "Specification.h"



class Figure
{
private:
	std::wstring _type;
	Point _location;
	bool whiteSide;







public:
	Figure();
	~Figure();

	bool whiteSide;

	virtual void move() = 0;

	const std::wstring& getType() const;
	const Point getLocation() const;
	void setLocation(int x, int y);







};

