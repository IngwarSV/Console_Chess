#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <bitset>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem> // creating directory for Saved Games and loading file with saved data
namespace fs = std::filesystem;
#include <Windows.h> // Setting console font

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

	int _halfTurn; // game turns: halfTurn * 2
	bool _CHECK;
	bool _gameOver;
	bool _moveCompleted;

	std::wstring _command; // for command line instructions
	std::wstring _logMessage; // for game notifications

	// methods
	void initialSetup();

	void drawGameField();

	////logicBlock2:

	void input(); // handling instructions

	void newGame();

	void saveGame();

	void loadGame();

	////logicBlock3:

	void mainLogic(Point currentPosition, Point newPosition);

	bool castling(Figure* king, Point currentPosition, Point newPosition);

	bool enPassant(Figure* figureToMove, Point currentPosition, Point newPosition);

	//// checking if move cause CHECK for the king
	bool isKingInDanger(Figure* figureToMove, Point currentPosition, Point newPosition);

	void promotion(Figure* figureToMove, Point newPosition);

	void deletingFigure(Figure* enemyFigure);

	void customGame(); // create new Game with certain positions of figures

	void clearData(); // deleting existing game data to load saved game / customize new game

	void parseFigureDataString(std::wstring col_type_loc); //parsing string into figure's data


public:
	Game();
	~Game();

	// methods
	void gameLoop();

	////logicBlock1:

	bool isCheck();

	bool isCheckmate();

	bool isDraw();


















	// getters for testing
	const Figure* getBoard(Point point) const;
	const std::unordered_set<Figure*>* getWhiteArmy() const;
	const std::unordered_set<Figure*>* getBlackArmy() const;
	const std::bitset<BOARD_SIZE>& getWArmyBit() const;
	const std::bitset<BOARD_SIZE>& getBArmyBit() const;
	const std::unordered_set<Figure*>* getCurrentArmy() const;
	const std::unordered_set<Figure*>* getEnemyArmy() const;
	const Figure* getEnPassantFigure() const;
	const Point getFirstEnPassantPoint() const;
	const int getHalfTurn() const;
	const bool getCHECKStatus() const;
	const bool getGameOverStatus() const;
	const bool getMoveCompletedStatus() const;
	const std::wstring& getCurrentCommand() const;
	const std::wstring& getLogMessage() const;

	// create new custom Game from string, for testing
	void loadGameDataString(std::wstring dataString);





	








};

