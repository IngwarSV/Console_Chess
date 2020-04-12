#pragma once

#include <iostream>
#include <string>
#include <set>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;

class Game
{
private:
	// attributes
	Figure*** _board = nullptr;
	std::wstring **_totalGameField;
	/*Figure* _board[BOARD_SIZE][BOARD_SIZE];
	std::wstring _totalGameField[GAME_FIELD_SIZE][GAME_FIELD_SIZE];*/
	std::set<Figure*> _whiteArmy;
	std::set<Figure*> _blackArmy;

	// Kings need special attitude
	Figure* _WKing = nullptr;
	Figure* _BKing = nullptr;

	std::wstring _command{};
	int _halfTurn;
	bool _CHECK;
	bool _gameOver;
	bool _moveIsAllowed;

	std::wstring _logMessage{};

	// methods
	void initialSetup();

	void startMenu();

	void drawGameField();

	void logicBlock1();

		void isDraw();

		void isCheckmate();

	void input();

	void newGame();

	void saveGame();

	void loadGame();

	void logic(Point currentPosition, Point newPosition);

		bool Castling(Figure* king, Point currentPosition, Point newPosition);

		bool isKingInDanger();

		void move();


	void endMenu();


public:
	Game();
	~Game();

	// attributes
	

	// methods
	void gameLoop();

};

