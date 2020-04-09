#pragma once
#include <string>



class Figure
{
private:
	std::string name;







public:
	Figure();
	~Figure();

	virtual void move() = 0;







};

