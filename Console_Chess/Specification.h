#pragma once

#include <string>

// WR, WN, WB, WQ, WK, WB, WN, WR
// WP, WP, WP, WP, WP, WP, WP, WP




// BP, BP, BP, BP, BP, BP, BP, BP
// BR, BN, BB, BQ, BK, BB, BN, BR


struct Point {
	int x = 0, y = 0;

	bool operator==(const Point& other) const {
		return this->x == other.x && this->y == other.y;
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
	const wchar_t COMMANDS_STRING[] = L"Commands: (N)ew, (L)oad, (S)ave\n\t   Move, e.g.: <a4-a5>\n";

	// "Black's move" string
	const wchar_t ENTER_COMMAND_STRING[] = L"Enter command: ";

	// Log Messages
	const std::wstring ErrorInvalidMoveParam = L"Invalid move command (e.g.: a2-a4): ";
	const std::wstring ErrorInvalidPos1 = L"Invalid parameter for current position of figure: ";
	const std::wstring ErrorInvalidPos2 = L"Invalid parameter for new position of figure: ";
	const std::wstring ErrorInvalidPos3 = L"No figure in your set on the position: ";
	const std::wstring ErrorMoveIsIllegal = L"Figure can't move: ";
	const std::wstring PreviousMove = L"Previous move: ";
	const std::wstring ErrorKingIsInDanger = L"Your King is in danger if: ";

	// Figures' starting positions

	// White Army
	const Point WR_INIT_POS1{ 0,0 };
	const Point WN_INIT_POS1{ 0,1 };
	const Point WB_INIT_POS1{ 0,2 };
	const Point WQ_INIT_POS{ 0,3 };
	
	const Point WK_INIT_POS{ 3,5 };
	//const Point WB_INIT_POS2{ 0,5 };
	const Point WB_INIT_POS2{ 4,3 };
	const Point WN_INIT_POS2{ 0,6 };
	const Point WR_INIT_POS2{ 0,7 };
	const Point WP_INIT_POS1{ 1,0 };

	// Black Army
	const Point BR_INIT_POS1{ 7,0 };
	const Point BN_INIT_POS1{ 7,1 };
	//const Point BB_INIT_POS1{ 7,2 };
	const Point BB_INIT_POS1{ 5,2 };
	//const Point BQ_INIT_POS{ 7,3 };
	const Point BQ_INIT_POS{ 5,4 };
	const Point BK_INIT_POS{ 7,4 };
	const Point BB_INIT_POS2{ 7,5 };
	const Point BN_INIT_POS2{ 7,6 };
	const Point BR_INIT_POS2{ 7,7 };
	const Point BP_INIT_POS1{ 6,0 };

}

















