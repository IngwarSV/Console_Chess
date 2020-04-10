#pragma once

// WR, WN, WB, WQ, WK, WB, WN, WR
// WP, WP, WP, WP, WP, WP, WP, WP




// BP, BP, BP, BP, BP, BP, BP, BP
// BR, BN, BB, BQ, BK, BB, BN, BR


struct Point {
	int x, y;
};

enum Color : wchar_t {
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
	const wchar_t ABCDEFGH_STRING[] = L"   a  b  c  d  e  f  g  h";

	// Figures' starting positions

	// White Army
	const Point WR_INIT_POS1{ 0,0 };
	const Point WN_INIT_POS1{ 0,1 };
	const Point WB_INIT_POS1{ 0,2 };
	const Point WQ_INIT_POS{ 0,3 };
	const Point WK_INIT_POS{ 0,4 };
	const Point WB_INIT_POS2{ 0,5 };
	const Point WN_INIT_POS2{ 0,6 };
	const Point WR_INIT_POS2{ 0,7 };
	const Point WP_INIT_POS1{ 1,0 };

	// Black Army
	const Point BR_INIT_POS1{ 7,0 };
	const Point BN_INIT_POS1{ 7,1 };
	const Point BB_INIT_POS1{ 7,2 };
	const Point BQ_INIT_POS{ 7,3 };
	const Point BK_INIT_POS{ 7,4 };
	const Point BB_INIT_POS2{ 7,5 };
	const Point BN_INIT_POS2{ 7,6 };
	const Point BR_INIT_POS2{ 7,7 };
	const Point BP_INIT_POS1{ 6,0 };




	// Amount of pieces in single Tetromino	
	const int PIECES = 4;

	// All 4 pieces have coordinates in 4x4 matrix
	const int DIMENSION = 4;

	// For console settings
	const int OUTPUT_SIZE_X = 50;
	const int OUTPUT_SIZE_Y = 30;

	// TotalGameField size
	const int GAME_FIELD_WIDTH = 25;
	const int GAME_FIELD_HEIGHT = 26;

	// PlayField size
	const int PLAY_FIELD_WIDTH = 17;
	const int PLAY_FIELD_HEIGHT = 22;

	// Initial Tetromino's position on PlayField
	const Point INIT_BLOCK_POS{ 7,0 };

	// Initial Tetromino's position on PreviewField
	const Point INIT_PREVIEW_BLOCK_POS{ PLAY_FIELD_WIDTH + 2, 2 };

	//Tetrominoes types
	const int BLOCKS_AMOUNT = 7;

	// Initial Tetromino's descending speed, one position every ~0.5 seconds
	const float INIT_SPEED = 0.5f;

	// for speed incrementing 
	const float SPEED_DELTA = 0.1f;

	// blocks to initiate incrementing
	const int BLOCKS_PER_ROUND = 10;
}

















