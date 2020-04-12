#pragma once

#include <iostream>
#include <string>
#include <set>
#include <bitset>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;

class Game
{
private:
	// attributes
	Figure*** _board;
	std::wstring **_totalGameField;
	
	//// sets for "White" and "Black" armies and pointers on them
	std::set<Figure*>* _whiteArmy;
	std::set<Figure*>* _blackArmy;
	std::set<Figure*>* _currentArmy;
	std::set<Figure*>* _enemyArmy;

	//// bitsets 0111 1111 for 8 figures (B, B, N, N, R, R, Q, Q) in army 
	//// including 1 place for promoted Queen
	std::bitset<BOARD_SIZE> _bit_whiteArmy{ 127 };
	std::bitset<BOARD_SIZE> _bit_blackArmy{ 127 };

	//pawns quantity (for draw calculating)
	int _pawnQuantity;

	//// Kings need special attitude
	Figure* _WKing;
	Figure* _BKing;

	std::wstring _command{};
	int _halfTurn;
	bool _CHECK;
	bool _gameOver;
	bool _moveCompleted;

	std::wstring _logMessage{};

	// methods
	void initialSetup();

	void startMenu();

	void drawGameField();

	void logicBlock1();

		bool isDraw();

		bool isCheck();

		bool isCheckmate();

	void input();

	void newGame();

	void saveGame();

	void loadGame();

	void logic(Point currentPosition, Point newPosition);

		bool Castling(Figure* king, Point currentPosition, Point newPosition);

		bool isKingInDanger(Figure* figureToMove, Point currentPosition, Point newPosition);

		void promotion(Figure* figureToMove, Point newPosition);

		void move();

		void deletingFigure(Figure* enemyFigure);


	void endMenu();


public:
	Game();
	~Game();

	// attributes
	

	// methods
	void gameLoop();

};

