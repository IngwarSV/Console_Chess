#include "Game.h"

void Game::initialSetup()
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
	initialSetup();
	_halfTurn = 1;
	_gameOver = false;
	_moveIsAllowed = false;
	_logMessage += L"\n";
}

Game::~Game()
{

}

void Game::startMenu()
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
		std::wcout << L'\n';
	}

	system("cls");

	std::wcout << WHITE_STRING;
	std::wcout << ABCDEFGH_STRING;
	
	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		for (int j = 0; j < GAME_FIELD_SIZE; ++j) {
			std::wcout << _totalGameField[i][j];
		}
		std::wcout << L'\n';
	}
	std::wcout << ABCDEFGH_STRING;
	std::wcout << BLACK_STRING;

	std::wcout << COMMANDS_STRING;
	
	if (_halfTurn % 2) {
		std::wcout << WHITE_MOVE_STRING;
	}
	else {
		std::wcout << BLACK_MOVE_STRING;
	}

	std::wcout << _logMessage;

	std::wcout << ENTER_COMMAND_STRING;
	
	

}

void Game::input()
{
	std::wstring command;
	//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
	std::getline(std::wcin, command);

	// Cheking "New Game", "Load Game", "Save Game" commands
	if (command[0] == L'N' || command[0] == L'n') {
		newGame();
		_moveIsAllowed = true;
		_gameOver = true;
		return;
	}
	else if (command[0] == L'L' || command[0] == L'l') {
		loadGame();
		_moveIsAllowed = true;
		return;
	}
	else if (command[0] == L'S' || command[0] == L's') {
		saveGame();
		_moveIsAllowed = false;
		return;
	}

	// checking parameters for Move command, at least 5 symbols are required, e.g. "a2-a4" or "b7 b4 "
	if (command.size() < 5) {
		_moveIsAllowed = false;
		
		_logMessage = ErrorInvalidMoveParam + command + L'\n';
		return;
	}

	// checking current position for the Figure, e.g "a1" == Point(0,0),"b3" == Point(2,1)
	Point currentPosition;

	wchar_t capitalLetter = L'A';
	wchar_t	lowercaseLetter = L'a';
	bool flag1 = true;
	bool flag2 = true;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (command[0] == capitalLetter || command[0] == lowercaseLetter) {
			currentPosition.y = i;
			flag1 = false;
		}
		
		if (command[1] == static_cast<wchar_t>(i + 49)) {
			currentPosition.x = i;
			flag2 = false;
		}

		capitalLetter += 1;
		lowercaseLetter += 1;
	}

	if (flag1 || flag2) {
		_moveIsAllowed = false;
		_logMessage = ErrorInvalidPos1 + command[0] + command[1] + L'\n';
		return;
	}

	// checking new position for the Figure, e.g "a1" == Point(0,0),"b3" == Point(2,1)
	Point newPosition;

	capitalLetter = L'A';
	lowercaseLetter = L'a';
	flag1 = true;
	flag2 = true;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (command[3] == capitalLetter || command[3] == lowercaseLetter) {
			newPosition.y = i;
			flag1 = false;
		}

		if (command[4] == static_cast<wchar_t>(i + 49)) {
			newPosition.x = i;
			flag2 = false;
		}

		capitalLetter += 1;
		lowercaseLetter += 1;
	}

	if (flag1 || flag2) {
		_moveIsAllowed = false;
		_logMessage = ErrorInvalidPos2 + command[3] + command[4] + L'\n';
		return;
	}

	// forwarding currentLocation and newLocation to logic block
	logic(currentPosition, newPosition);
}

void Game::newGame()
{
}

void Game::saveGame()
{
}

void Game::loadGame()
{
}

void Game::logic(Point currentPosition, Point newPosition)
{
	// identifying entered position with figures' positions on the board  
	Figure* chosenFigure = nullptr;

	if (_halfTurn % 2) {
		for (auto figure : _whiteArmy) {
			Point figurePosition = figure->getLocation();

			if (figurePosition.x == currentPosition.x && figurePosition.y == currentPosition.y) {
				chosenFigure = figure;
			}
		}
	}
	else {
		for (auto figure : _blackArmy) {
			Point figurePosition = figure->getLocation();

			if (figurePosition.x == currentPosition.x && figurePosition.y == currentPosition.y) {
				chosenFigure = figure;
			}
		}
	}

	if (!chosenFigure) {
		_moveIsAllowed = false;
		std::wstring position{};
		position += static_cast<wchar_t>(currentPosition.y + 97);
		position += static_cast<wchar_t>(currentPosition.x + 49);

		_logMessage = ErrorInvalidPos3 + position + L'\n';
		return;
	}

	//_logMessage = chosenFigure->getFigureName() + L'\n';

	







}





void Game::endMenu()
{
}

void Game::gameLoop()
{
	startMenu();

	while (!_gameOver) {
		while (!_moveIsAllowed) {
			drawGameField();
			input();
		}
	}

	endMenu();
}
