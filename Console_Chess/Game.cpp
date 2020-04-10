#include "Game.h"

void Game::setup()
{
	// Setting totalGameField
	int fieldEdge = GAME_FIELD_SIZE - 1;

	_totalGameField[0][0] = L" \u2554";
	_totalGameField[0][fieldEdge] = L"\u2557 ";
	_totalGameField[fieldEdge][0] = L" \u255A";
	_totalGameField[fieldEdge][fieldEdge] = L"\u255D ";


	for (int i = 1; i < fieldEdge; ++i) {
		if (i % 2) {
			_totalGameField[0][i] = L"\u2550\u2550";
			_totalGameField[fieldEdge][i] = L"\u2550\u2550";
		}
		else {
			_totalGameField[0][i] = L"\u2564";
			_totalGameField[fieldEdge][i] = L"\u2567";
		}
	}

	for (int i = 1, counter = 0; i < fieldEdge; ++i) {
		if (i % 2) {
			counter += 1;
			_totalGameField[i][0] = std::to_wstring(counter) + L"\u2551";
			_totalGameField[i][fieldEdge] = L"\u2551" + std::to_wstring(counter);
		}
		else {
			_totalGameField[i][0] = L" \u255F";
			_totalGameField[i][fieldEdge] = L"\u2562 ";
		}

	}

	for (int i = 1; i < fieldEdge; ++i) {
		for (int j = 1; j < fieldEdge; ++j) {
			if (i % 2) {
				if (j % 2) {
					_totalGameField[i][j] = L"  ";
					
				}
				else {
					_totalGameField[i][j] = L"\u2502";
					
				}
			}
			else {
				if (j % 2) {
					_totalGameField[i][j] = L"\u2500\u2500";
				}
				else {
					_totalGameField[i][j] = L"\u253C";
				}
			}
		}
	}


	// Setting board
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	// Creating and deploying figures on the board

	// White Army
	_whiteArmy.insert(new F_King(WHITE, WK_INIT_POS));
	_whiteArmy.insert(new F_Queen(WHITE, WQ_INIT_POS));
	_whiteArmy.insert(new F_Bishop(WHITE, WB_INIT_POS1));
	_whiteArmy.insert(new F_Bishop(WHITE, WB_INIT_POS2));
	_whiteArmy.insert(new F_Knight(WHITE, WN_INIT_POS1));
	_whiteArmy.insert(new F_Knight(WHITE, WN_INIT_POS2));
	_whiteArmy.insert(new F_Rook(WHITE, WR_INIT_POS1));
	_whiteArmy.insert(new F_Rook(WHITE, WR_INIT_POS2));

	// Black Army
	_blackArmy.insert(new F_King(BLACK, BK_INIT_POS));
	_blackArmy.insert(new F_Queen(BLACK, BQ_INIT_POS));
	_blackArmy.insert(new F_Bishop(BLACK, BB_INIT_POS1));
	_blackArmy.insert(new F_Bishop(BLACK, BB_INIT_POS2));
	_blackArmy.insert(new F_Knight(BLACK, BN_INIT_POS1));
	_blackArmy.insert(new F_Knight(BLACK, BN_INIT_POS2));
	_blackArmy.insert(new F_Rook(BLACK, BR_INIT_POS1));
	_blackArmy.insert(new F_Rook(BLACK, BR_INIT_POS2));

	// Pawns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		Point tempWhite = WP_INIT_POS1;
		Point tempBlack = BP_INIT_POS1;
		tempWhite.y += i;
		tempBlack.y += i;

		_whiteArmy.insert(new F_Pawn(WHITE, tempWhite));
		_blackArmy.insert(new F_Pawn(BLACK, tempBlack));
	}
	

}

Game::Game()
{
	/*Figure* _board[BOARD_SIZE][BOARD_SIZE];
	std::string _totalGameField[GAME_FIELD][GAME_FIELD];
	std::vector<Figure*> _whiteArmy;
	std::vector<Figure*> _blackArmy;*/

	setup();

	







}

Game::~Game()
{

}

void Game::drawGameField()
{
	// updating board's situation considering figures' positions
	for (auto figure : _whiteArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	for (Figure* figure : _blackArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}


	// updating totalGameField considering situation on the board
	for (int i = 1, k = 0; i < GAME_FIELD_SIZE; i += 2, k += 1) {
		for (int j = 1, l = 0; j < GAME_FIELD_SIZE; j += 2, l += 1) {
			if (_board[k][l]) {
				_totalGameField[i][j] = _board[k][l]->getFigureName();
			}
			else {
				_totalGameField[i][j] = L"  ";
			}
			
		}
		std::wcout << '\n';
	}

	std::wcout << ABCDEFGH_STRING << L'\n';

	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		for (int j = 0; j < GAME_FIELD_SIZE; ++j) {
			std::wcout << _totalGameField[i][j];
		}
		std::wcout << L'\n';
	}
	std::wcout << ABCDEFGH_STRING << L'\n';
}

void Game::run()
{




}
