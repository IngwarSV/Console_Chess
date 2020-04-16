#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <bitset>
#include <fstream>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;

class Game
{
private:
	// attributes
	
	//// Board[SIZE][SIZE], BOARD_SIZE = 8;
	Figure*** _board; 

	//// TotalGameField[SIZE][SIZE], GAME_FIELD_SIZE = 17;
	std::wstring **_totalGameField; 
	
	//// sets for "White" and "Black" armies and pointers on them
	std::unordered_set<Figure*>* _whiteArmy;
	std::unordered_set<Figure*>* _blackArmy;
	std::unordered_set<Figure*>* _currentArmy;
	std::unordered_set<Figure*>* _enemyArmy;

	//// bitsets 0111 1111 for 8 figures (B1, B2, N1, N2, R1, R2, Q1, Q2) in army 
	std::bitset<BOARD_SIZE> _bit_whiteArmy{ 127 };// including 1 place for promoted Queen 
	std::bitset<BOARD_SIZE> _bit_blackArmy{ 127 };

	int _pawnQuantity; //pawns quantity (for draw calculatings)

	//// pointers for kings for quick access
	Figure* _WKing;
	Figure* _BKing;
	Figure* _activeKing;

	// for "en passant" actions 
	Figure* _enPassantFigure; // pawn that just made en Passant
	Point _firstEnPassantPoint; // square that was skipped

	int _halfTurn; // game turns * 2
	bool _CHECK;
	bool _gameOver;
	bool _moveCompleted;

	std::wstring _command; // for command line instructions
	std::wstring _logMessage; // for game notifications

	// methods
	void initialSetup();

	void drawGameField();

	////logicBlock1:

	bool isCheck();

	bool isCheckmate();

	bool isDraw();

	
	void input(); // handling instructions

	////logicBlock2:
	void newGame();

	void saveGame(); // need to be implemented

	void loadGame(); // need to be implemented

	////logicBlock3:
	void mainLogic(Point currentPosition, Point newPosition);

	bool castling(Figure* king, Point currentPosition, Point newPosition);

	bool enPassant(Figure* figureToMove, Point currentPosition, Point newPosition);

	//// checking if move cause check for the king
	bool isKingInDanger(Figure* figureToMove, Point currentPosition, Point newPosition);

	void promotion(Figure* figureToMove, Point newPosition);

	void deletingFigure(Figure* enemyFigure);

	void customGame(); // create new Game with certain positions of figures


public:
	Game();
	~Game();

	// methods
	void gameLoop();
};

