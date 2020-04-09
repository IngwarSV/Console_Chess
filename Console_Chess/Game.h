#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Specification.h"
#include "Figure.h"

using namespace DEF_SETT;

class Game
{
private:
	Figure* _board[BOARD_SIZE][BOARD_SIZE];
	std::wstring _totalGameField[GAME_FIELD_SIZE][GAME_FIELD_SIZE];
	std::vector<Figure*> _whiteArmy;
	std::vector<Figure*> _blackArmy;



	// methods


	// TODO
	void setup();

	void saveGame();

	void loadGame();


public:
	Game();
	~Game();

	




	// TODO
	void drawGameField();


	void run();








};

