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

	// Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	// Creating and deploying figures on the board

	// White Army
	_whiteArmy.insert(_WKing);
	_whiteArmy.insert(new F_Queen(Color::WHITE, WQ_INIT_POS));
	_whiteArmy.insert(new F_Bishop(Color::WHITE, WB_INIT_POS1));
	_whiteArmy.insert(new F_Bishop(Color::WHITE, WB_INIT_POS2));
	_whiteArmy.insert(new F_Knight(Color::WHITE, WN_INIT_POS1));
	_whiteArmy.insert(new F_Knight(Color::WHITE, WN_INIT_POS2));
	_whiteArmy.insert(new F_Rook(Color::WHITE, WR_INIT_POS1));
	_whiteArmy.insert(new F_Rook(Color::WHITE, WR_INIT_POS2));

	// Black Army
	
	_blackArmy.insert(_BKing);
	_blackArmy.insert(new F_Queen(Color::BLACK, BQ_INIT_POS));
	_blackArmy.insert(new F_Bishop(Color::BLACK, BB_INIT_POS1));
	_blackArmy.insert(new F_Bishop(Color::BLACK, BB_INIT_POS2));
	_blackArmy.insert(new F_Knight(Color::BLACK, BN_INIT_POS1));
	_blackArmy.insert(new F_Knight(Color::BLACK, BN_INIT_POS2));
	_blackArmy.insert(new F_Rook(Color::BLACK, BR_INIT_POS1));
	_blackArmy.insert(new F_Rook(Color::BLACK, BR_INIT_POS2));

	// Pawns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		Point tempWhite = WP_INIT_POS1;
		Point tempBlack = BP_INIT_POS1;
		tempWhite.y += i;
		tempBlack.y += i;

		_whiteArmy.insert(new F_Pawn(Color::WHITE, tempWhite));
		_blackArmy.insert(new F_Pawn(Color::BLACK, tempBlack));
	}

	// updating board's situation considering figures' positions
	for (auto figure : _whiteArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	for (Figure* figure : _blackArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}
}

Game::Game()
{
	_board = new Figure** [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_board[i] = new Figure* [BOARD_SIZE];
	}

	_totalGameField = new std::wstring*[GAME_FIELD_SIZE];
	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		_totalGameField[i] = new std::wstring[GAME_FIELD_SIZE];
	}

	_WKing = new F_King(Color::WHITE, WK_INIT_POS);
	_BKing = new F_King(Color::BLACK, BK_INIT_POS);

	initialSetup();
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;
	_moveIsAllowed = false;
	_logMessage += L"\n";
}

Game::~Game()
{
	// deleting board
	for (int i = 0; i < BOARD_SIZE; ++i) {
		delete[] _board[i];
	}
	delete[] _board;

	// deleting totalGameField
	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		delete[] _totalGameField[i];
	}
	delete[] _totalGameField;

	// delete Figures* in Armies

}

void Game::startMenu()
{
}

void Game::drawGameField()
{
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
	//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
	std::getline(std::wcin, _command);

	// Cheking "New Game", "Load Game", "Save Game" commands
	if (_command[0] == L'N' || _command[0] == L'n') {
		newGame();
		_moveIsAllowed = true;
		_gameOver = true;
		return;
	}
	else if (_command[0] == L'L' || _command[0] == L'l') {
		loadGame();
		_moveIsAllowed = true;
		return;
	}
	else if (_command[0] == L'S' || _command[0] == L's') {
		saveGame();
		_moveIsAllowed = false;
		return;
	}

	// checking parameters for Move command, at least 5 symbols are required, e.g. "a2-a4" or "b7 b4 "
	if (_command.size() < 5) {
		_moveIsAllowed = false;
		
		_logMessage = ErrorInvalidMoveParam + _command + L'\n';
		return;
	}

	// checking current position for the Figure, e.g "a1" == Point(0,0),"b3" == Point(2,1)
	Point currentPosition;

	wchar_t capitalLetter = L'A';
	wchar_t	lowercaseLetter = L'a';
	bool flag1 = true;
	bool flag2 = true;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (_command[0] == capitalLetter || _command[0] == lowercaseLetter) {
			currentPosition.y = i;
			flag1 = false;
		}
		
		if (_command[1] == static_cast<wchar_t>(i + 49)) {
			currentPosition.x = i;
			flag2 = false;
		}

		capitalLetter += 1;
		lowercaseLetter += 1;
	}

	if (flag1 || flag2) {
		_moveIsAllowed = false;
		_logMessage = ErrorInvalidPos1 + _command[0] + _command[1] + L'\n';
		return;
	}

	// checking new position for the Figure, e.g "a1" == Point(0,0),"b3" == Point(2,1)
	Point newPosition;

	capitalLetter = L'A';
	lowercaseLetter = L'a';
	flag1 = true;
	flag2 = true;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (_command[3] == capitalLetter || _command[3] == lowercaseLetter) {
			newPosition.y = i;
			flag1 = false;
		}

		if (_command[4] == static_cast<wchar_t>(i + 49)) {
			newPosition.x = i;
			flag2 = false;
		}

		capitalLetter += 1;
		lowercaseLetter += 1;
	}

	if (flag1 || flag2) {
		_moveIsAllowed = false;
		_logMessage = ErrorInvalidPos2 + _command.substr(3,2) + L'\n';
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

			if (figurePosition == currentPosition) {
				chosenFigure = figure;
			}
		}
	}
	else {
		for (auto figure : _blackArmy) {
			Point figurePosition = figure->getLocation();

			if (figurePosition == currentPosition) {
				chosenFigure = figure;
			}
		}
	}

	if (!chosenFigure) {
		_moveIsAllowed = false;
		
		_logMessage = ErrorInvalidPos3 + _command.substr(0, 2) + L'\n';
		return;
	}

	// checking if chosenFigure can execute command
	bool moveIsLegal = false;

	////checking for Castling
	if (chosenFigure->_firstMove) {
		if (chosenFigure->getType == Type::KING) {
			if (newPosition == Point{ chosenFigure->getLocation().x, 2 } ||
				newPosition == Point{ chosenFigure->getLocation().x, 6 }) {
				Castling(chosenFigure, currentPosition, newPosition);
			}
			
		}
	}


	




	auto v_possibleMoves = chosenFigure->getPossibleMoves(_board);

	

	for (auto possiblePosition : *v_possibleMoves) {
		if (newPosition == possiblePosition) {
			moveIsLegal = true;
			break;
		}
	}

	if (!moveIsLegal) {
		_moveIsAllowed = false;
		
		_logMessage = ErrorMoveIsIllegal + _command.substr(0, 5) + L'\n';
		return;
	}

	// checking if figure's movement doesn't endanger the king
	Figure* enemyFigure = nullptr;
	
	if (_board[newPosition.x][newPosition.y]) {
		enemyFigure = _board[newPosition.x][newPosition.y];

		if (_halfTurn % 2) {
			_blackArmy.erase(enemyFigure);
		}
		else {
			_whiteArmy.erase(enemyFigure);
		}
	}
	_board[currentPosition.x][currentPosition.y] = nullptr;
	_board[newPosition.x][newPosition.y] = chosenFigure;
	chosenFigure->setLocation(newPosition);

	if (isKingInDanger()) {
		_board[currentPosition.x][currentPosition.y] = chosenFigure;
		_board[newPosition.x][newPosition.y] = enemyFigure;
		chosenFigure->setLocation(currentPosition);
		
		if (enemyFigure) {
			if (_halfTurn % 2) {
				_blackArmy.insert(enemyFigure);
			}
			else {
				_whiteArmy.insert(enemyFigure);
			}
		}
		
		_logMessage = ErrorKingIsInDanger + _command.substr(0, 5) + L'\n';
		_moveIsAllowed = false;

		return;
	}

	// Deleting enemy's figure (if needed) and moving figure on new position
	if (enemyFigure) {
		delete enemyFigure;
	}
	chosenFigure->_firstMove = false;
	_logMessage = PreviousMove + _command.substr(0, 5) + L'\n';
}

bool Game::Castling(Figure* king, Point currentPosition, Point newPosition)
{
	// Checking conditions
	if (newPosition.y > currentPosition.y) {
		Figure* tempFigure = _board[newPosition.x][BOARD_SIZE - 1];
		
		if (tempFigure && tempFigure->getType() == Type::ROOK && tempFigure->_firstMove) {
			Point tempPosition{ newPosition.x, newPosition.y - 1 };

					}
				}
				else {
					Figure* tempFigure = _board[newPosition.x][0];

					if (tempFigure && tempFigure->getType() == Type::ROOK && tempFigure->_firstMove) {
						Point tempPosition{ newPosition.x, newPosition.y + 1 };

						moveIsLegal = Castling(currentPosition, tempPosition, newPosition);
					}
				}

	
	
	
	Figure* king = _board[currentPosition.x][currentPosition.y];

	if (!_board[tempPosition.x][tempPosition.y]) {
		_board[tempPosition.x][tempPosition.y] = king;
		king->setLocation(tempPosition);
	}


	if (isKingInDanger()) {
		_board[currentPosition.x][currentPosition.y] = chosenFigure;
		_board[newPosition.x][newPosition.y] = enemyFigure;
		chosenFigure->setLocation(currentPosition);
	}








	return false;
}

bool Game::isKingInDanger()
{
	if (_halfTurn % 2) {
		Point kingPosition = _WKing->getLocation();

		for (auto it = _blackArmy.cbegin(); it != _blackArmy.cend(); ++it) {
			auto v_possibleMoves = (*it)->getPossibleMoves(_board);

			for (auto possiblePosition : *v_possibleMoves) {
				if (kingPosition == possiblePosition) {
					return true;
				}
			}
		}
	}
	else {
		Point kingPosition = _BKing->getLocation();

		for (auto it = _whiteArmy.cbegin(); it != _whiteArmy.cend(); ++it) {
			auto v_possibleMoves = (*it)->getPossibleMoves(_board);

			for (auto possiblePosition : *v_possibleMoves) {
				if (kingPosition == possiblePosition) {
					return true;
				}
			}
		}
	}

	return false;
}






void Game::endMenu()
{
}

void Game::gameLoop()
{
	startMenu();

	while (!_gameOver) {
		if (isKingInDanger()) {
			_CHECK = true;
		}
		while (!_moveIsAllowed) {
			drawGameField();
			input();
		}
		_halfTurn += 1;
	}

	endMenu();
}
