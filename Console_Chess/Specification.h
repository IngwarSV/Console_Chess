#pragma once

#include <string>

struct Point {
	int x = 0, y = 0;

	bool operator==(const Point& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Point& other) const {
		return this->x != other.x || this->y != other.y;
	}
};

enum class Color : wchar_t {
	BLACK = 66,
	WHITE = 87
};

enum class Type : wchar_t {
	KING = 75,
	QUEEN = 81,
	BISHOP = 66,
	KNIGHT = 78,
	ROOK = 82,
	PAWN = 80
};

namespace DEF_SETT {
	// Board size
	const int BOARD_SIZE = 8;

	// TotalField size
	const int GAME_FIELD_SIZE = 17;
	
	//pawns quantity (for draw calculating)
	const int PAWN_QUANTITY = 16;
	
	// Saved games path
	const char SAVED_GAMES_PATH[] = "SavedGames.txt";

	// "a  b  c  d  e  f  g  h" string
	const wchar_t ABCDEFGH_STRING[] = L"   a  b  c  d  e  f  g  h\n";

	// "White" string
	const wchar_t WHITE_STRING[] = L"\t   White\n";

	// "Black" string
	const wchar_t BLACK_STRING[] = L"\t   Black\n";

	// "White's move" string
	const wchar_t WHITE_MOVE_STRING[] = L"Current turn: WHITE\n";

	// "Black's move" string
	const wchar_t BLACK_MOVE_STRING[] = L"Current turn: BLACK\n";

	// "Black's move" string
	const wchar_t COMMANDS_STRING[] = 
		L"Commands: (N)ew, (L)oad, (S)ave, (C)ustom,\n\t  Move e.g.: (A4 A5)\n";

	// "Black's move" string
	const wchar_t ENTER_COMMAND_STRING[] = L"Enter command: ";

	// Log Messages
	const std::wstring NewGameString = L"New Game!\n";
	const std::wstring ErrorInvalidMoveParam = L"Invalid move command, enter e.g.: (A2 A4): ";
	const std::wstring ErrorInvalidPos1 = L"Invalid parameter for current position of figure: ";
	const std::wstring ErrorInvalidPos2 = L"Invalid parameter for new position of figure: ";
	const std::wstring ErrorInvalidPos3 = L"No figure in your set on the position: ";
	const std::wstring ErrorCastlingString = L"Can't execute castling: ";
	const std::wstring CastlingPerfomed = L"Castling executed: ";
	const std::wstring ErrorenPassantString = L"Can't execute enPassant: ";
	const std::wstring enPassantPerformedString = L"enPassant executed: ";
	const std::wstring ErrorMoveIsIllegal = L"Figure can't move: ";
	const std::wstring PreviousMoveString = L"Previous move: ";
	const std::wstring ErrorKingIsInDanger = L"Your King is in danger if: ";
	const std::wstring ChoosePromotionString = L"Choose promotion (Q), (B), (N), (R)\n";
	const std::wstring ErrorPromotionType1 = L"Error type of figure: ";
	const std::wstring ErrorPromotionType2 = L"\nChoose promotion (Q), (B), (N), (R)\n";
	const std::wstring DrawStalemateString = L"DRAW: stalemate\n";
	const std::wstring impossibleCheckmate1 = L"DRAW: two kings left\n";
	const std::wstring impossibleCheckmate2 = 
		L"DRAW: king with/without bishop versus king and\nbishop(bishops) on the same color\n";
	const std::wstring impossibleCheckmate3 = L"DRAW: king and knight versus king\n";
	const std::wstring ErrorCheckString = L"Warning: C H E C K!\n";
	const std::wstring ErrorCheckmateString = L"CHECKMATE: G A M E  O V E R!\n";
	const std::wstring EnteringCustomString = 
		L"Custom mode: (D)one, (Q)uit,\nPlace figures: (WQA2), (BBC7),\n(BKE81)-\"1\"-true for first move\n";
	const std::wstring ErrorPlaceKingsString = L"Please place black and white kings\n";
	const std::wstring ChooseSideToMoveString = L"Choose side to move first: W / B ?\n";
	const std::wstring NewCustomGameString = L"New Custom Game!\n";
	const std::wstring ErrorDataCustomString = L"Invalid data to place figure\n";
	const std::wstring ErrorLocCustomString = L"Invalid parameter for location of figure: ";
	const std::wstring ErrorLocOccupiedCustomString = L"Location is occupied: ";
	const std::wstring ErrorTypeCustomString = L"Invalid parameter for type of the figure: ";
	const std::wstring ErrorColorCustomString = L"Invalid parameter for color of the figure: ";
	const std::wstring FigureIsPlacedString = L"Figure is placed: ";
	const std::wstring SaveGameAsString = L"Save as (_.txt): ";

	//const std::wstring ChooseSideToMoveSetString = L"Choose side to move: W / B ?\n";

	// Figures' starting positions

	//// White Army
	const Point WR_INIT_POS1{ 7,0 };
	const Point WN_INIT_POS1{ 7,1 };
	const Point WB_INIT_POS1{ 7,2 };
	const Point WQ_INIT_POS{ 7,3 };
	const Point WK_INIT_POS{ 7,4 };
	const Point WB_INIT_POS2{ 7,5 };
	const Point WN_INIT_POS2{ 7,6 };
	const Point WR_INIT_POS2{ 7,7 };
	const Point WP_INIT_POS1{ 6,0 };
	
	//// Black Army
	const Point BR_INIT_POS1{ 0,0 };
	const Point BN_INIT_POS1{ 0,1 };
	const Point BB_INIT_POS1{ 0,2 };
	const Point BQ_INIT_POS{ 0,3 };
	const Point BK_INIT_POS{ 0,4 };
	const Point BB_INIT_POS2{ 0,5 };
	const Point BN_INIT_POS2{ 0,6 };
	const Point BR_INIT_POS2{ 0,7 };
	const Point BP_INIT_POS1{ 1,0 };


	// serial number of bits for 8 figures: N1, N2, B1, B2, R1, R2, Q1, Q2 in bitsets
	const int bit_F_Knight1 = 0;
	const int bit_F_Knight2 = 1;
	const int bit_F_Bishop1 = 2;
	const int bit_F_Bishop2 = 3;
	const int bit_F_Rook1 = 4;
	const int bit_F_Rook2 = 5;
	const int bit_F_Queen1 = 6;
	const int bit_F_Queen2 = 7;
}


















