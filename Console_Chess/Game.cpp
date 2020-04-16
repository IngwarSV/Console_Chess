#include "Game.h"

void Game::initialSetup()
{
	// Setting totalGameField 17 x 17
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

	for (int i = 1, counter = BOARD_SIZE; i < fieldEdge; ++i) {
		if (i % 2) {
			_totalGameField[i][0] = std::to_wstring(counter) + L"\u2551";
			_totalGameField[i][fieldEdge] = L"\u2551" + std::to_wstring(counter);
			counter -= 1;
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

	// Creating armies with figures 

	//// White Army
	_WKing = new F_King(Color::WHITE, WK_INIT_POS);
	_whiteArmy->insert(_WKing);
	_whiteArmy->insert(new F_Queen(Color::WHITE, WQ_INIT_POS));
	_whiteArmy->insert(new F_Bishop(Color::WHITE, WB_INIT_POS1));
	_whiteArmy->insert(new F_Bishop(Color::WHITE, WB_INIT_POS2));
	_whiteArmy->insert(new F_Knight(Color::WHITE, WN_INIT_POS1));
	_whiteArmy->insert(new F_Knight(Color::WHITE, WN_INIT_POS2));
	_whiteArmy->insert(new F_Rook(Color::WHITE, WR_INIT_POS1));
	_whiteArmy->insert(new F_Rook(Color::WHITE, WR_INIT_POS2));

	//// Black Army
	_BKing = new F_King(Color::BLACK, BK_INIT_POS);
	_blackArmy->insert(_BKing);
	_blackArmy->insert(new F_Queen(Color::BLACK, BQ_INIT_POS));
	_blackArmy->insert(new F_Bishop(Color::BLACK, BB_INIT_POS1));
	_blackArmy->insert(new F_Bishop(Color::BLACK, BB_INIT_POS2));
	_blackArmy->insert(new F_Knight(Color::BLACK, BN_INIT_POS1));
	_blackArmy->insert(new F_Knight(Color::BLACK, BN_INIT_POS2));
	_blackArmy->insert(new F_Rook(Color::BLACK, BR_INIT_POS1));
	_blackArmy->insert(new F_Rook(Color::BLACK, BR_INIT_POS2));

	//// Pawns
	_pawnQuantity = PAWN_QUANTITY;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		Point tempWhite = WP_INIT_POS1;
		Point tempBlack = BP_INIT_POS1;
		tempWhite.y += i;
		tempBlack.y += i;

		_whiteArmy->insert(new F_Pawn(Color::WHITE, tempWhite));
		_blackArmy->insert(new F_Pawn(Color::BLACK, tempBlack));
	}

	// updating board's situation considering figures' positions
	for (auto figure : *_whiteArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	for (Figure* figure : *_blackArmy) {
		Point location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	// initializing rest of the attributes
	_currentArmy = _whiteArmy;
	_enemyArmy = _blackArmy;

	// for "en passant" actions 
	_enPassantFigure = nullptr; // pawn that just made en Passant
	_firstEnPassantPoint = Point{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
	_halfTurn = 0;
	_CHECK = false;
	_gameOver = false;
	_moveCompleted = false;
	
	_command = L"\n";
	_logMessage = NewGameString;
}


Game::Game()
{
	// creating Board[8][8]
	this->_board = new Figure** [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_board[i] = new Figure* [BOARD_SIZE];
	}

	// creating totalGameField[17][17]
	this->_totalGameField = new std::wstring*[GAME_FIELD_SIZE];
	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		_totalGameField[i] = new std::wstring[GAME_FIELD_SIZE];
	}

	// creating white and black sets
	this->_whiteArmy = new std::unordered_set<Figure*>();
	this->_blackArmy = new std::unordered_set<Figure*>();
	
	initialSetup();
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

	// deleting Armies
	for (auto figure : *_whiteArmy) {
		delete figure;
	}
	delete _whiteArmy;

	for (auto figure : *_blackArmy) {
		delete figure;
	}
	delete _blackArmy;
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

	// drawing totalGameField
	std::wcout << BLACK_STRING;
	std::wcout << ABCDEFGH_STRING;
	
	for (int i = 0; i < GAME_FIELD_SIZE; ++i) {
		for (int j = 0; j < GAME_FIELD_SIZE; ++j) {
			std::wcout << _totalGameField[i][j];
		}
		std::wcout << L'\n';
	}

	std::wcout << ABCDEFGH_STRING;
	std::wcout << WHITE_STRING;
	
	std::wcout << COMMANDS_STRING;
	
	if (_halfTurn % 2) {
		std::wcout << WHITE_MOVE_STRING;
	}
	else {
		std::wcout << BLACK_MOVE_STRING;
	}

	// showing notifications
	std::wcout << _logMessage;

}


bool Game::isCheck()
{
	Point kingPosition = _activeKing->getLocation();

	for (auto enemyFigure : *_enemyArmy) {
		auto v_possibleMoves = enemyFigure->getPossibleMoves(_board);

		for (auto possiblePosition : *v_possibleMoves) {
			if (kingPosition == possiblePosition) {
				return true;
			}
		}
	}

	return false;
}


bool Game::isCheckmate()
{
	Point kingLocation = _activeKing->getLocation();
	
	// checking if king can escape check by himself
	auto v_possibleMoves = _activeKing->getPossibleMoves(_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (!isKingInDanger(_activeKing, kingLocation, possiblePosition)) {
			_logMessage += ErrorCheckString;
			return false;
		}
	}
	
	// checking if army can protect their king 
	// (test using king's moves is repeating, but mostly this second check won't be performed)

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(_board);
		Point figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				_logMessage += ErrorCheckString;
				return false;
			}
		}

		//// checking if enPassant can be performed to protect the king
		if (figure->getType() == Type::PAWN && _enPassantFigure) {
			if (enPassant(figure, figure->getLocation(), _firstEnPassantPoint)) {
				_logMessage += ErrorCheckString;
				return false;
			}
		}
	}

	// Game Over
	_logMessage += ErrorCheckmateString;
	return true;
}


bool Game::isDraw()
{
	// checking stalemate
	bool hasLegalMove = false;

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(_board);
		Point figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				hasLegalMove = true;
				break;
			}
		}

		// checking for enPassant move
		if (figure->getType() == Type::PAWN && _enPassantFigure && !hasLegalMove) {
			if (enPassant(figure, figure->getLocation(), _firstEnPassantPoint)) {
				hasLegalMove = true;
				break;
			}
		}
	}

	if (!hasLegalMove) {
		_logMessage = DrawStalemateString;
		return true;
	}

	// checking impossibility of checkmate
	std::bitset<BOARD_SIZE> _bit_temp = _bit_whiteArmy | _bit_blackArmy;

	//// cheking for pawns
	if (_pawnQuantity > 0) {
		return false;
	}

	//// two kings left (there is no bit for kings in the bitsets)
	if (!_bit_temp.to_ulong()) {
		_logMessage = impossibleCheckmate1;
		return true;
	}

	//// king with/without bishop versus king and bishop(bishops) on the same color
	if (_bit_temp.to_ulong() == 4Ul || _bit_temp.to_ulong() == 8Ul) {
		_logMessage = impossibleCheckmate2;
		return true;
	}

	//// king and knight versus king
	if (_bit_temp.to_ulong() == 1Ul && _bit_whiteArmy != _bit_blackArmy) {
		_logMessage = impossibleCheckmate3;
		return true;
	}

	return false;
}


void Game::input()
{
	std::wcout << ENTER_COMMAND_STRING;
	std::getline(std::wcin, _command);

	// Cheking "New Game", "Load Game", "Save Game" commands
	if (_command[0] == L'N') {
		newGame();
		_moveCompleted = true;
		return;
	}
	if (_command[0] == L'L') {
		loadGame();
		_moveCompleted = false;
		return;
	}
	if (_command[0] == L'S') {
		saveGame();
		_moveCompleted = false;
		return;
	}
	if (_command.substr(0, 3) == L"C") {
		customGame();
		_moveCompleted = true;
		return;
	}

	// checking parameters for Move instruction, at least 5 symbols are required, e.g. "A2-A4", "B7 B4 "
	if (_command.size() < 5) {
		_moveCompleted = false;
		
		_logMessage = ErrorInvalidMoveParam + _command + L'\n';
		return;
	}

	// checking and converting the entered current position for the figure, 
	// e.g "a8" == Point(0,0),"b3" == Point(5,1)
	Point currentPosition;

	wchar_t capitalLetter = L'A';
	bool flag1 = true;
	bool flag2 = true;

	for (int i = 0, j = BOARD_SIZE - 1; i < BOARD_SIZE; ++i) {
		if (_command[0] == capitalLetter) {
			currentPosition.y = i;
			flag1 = false;
		}
		
		if (_command[1] == static_cast<wchar_t>(i + 49)) {
			currentPosition.x = j - i;
			flag2 = false;
		}
		capitalLetter += 1;
	}

	if (flag1 || flag2) {
		_moveCompleted = false;
		_logMessage = ErrorInvalidPos1 + _command[0] + _command[1] + L'\n';
		return;
	}

	// checking and converting the entered new position for the figure, 
	// e.g "a1" == Point(0,0),"b3" == Point(2,1)
	Point newPosition;

	capitalLetter = L'A';
	flag1 = true;
	flag2 = true;

	for (int i = 0, j = BOARD_SIZE - 1; i < BOARD_SIZE; ++i) {
		if (_command[3] == capitalLetter) {
			newPosition.y = i;
			flag1 = false;
		}

		if (_command[4] == static_cast<wchar_t>(i + 49)) {
			newPosition.x = j - i;
			flag2 = false;
		}
		capitalLetter += 1;
	}

	if (flag1 || flag2) {
		_moveCompleted = false;
		_logMessage = ErrorInvalidPos2 + _command.substr(3,2) + L'\n';
		return;
	}

	// forwarding currentLocation and newLocation to next logic block
	mainLogic(currentPosition, newPosition);
}


void Game::newGame()
{
	// deleting current figures
	for (auto figure : *_whiteArmy) {
		delete figure;
	}
	_whiteArmy->clear();

	for (auto figure : *_blackArmy) {
		delete figure;
	}
	_blackArmy->clear();

	// launching initial setup
	initialSetup();
}


void Game::saveGame()
{
	_logMessage = SaveGameAsString;
	std::ofstream fout(SAVED_GAMES_PATH);
	std::string fileName;

	if (fout) {
		std::getline(std::cin, fileName);
		fileName += ".txt";

		fout << fileName << "\n";




	}
	fout.close();


	std::ifstream fin(SAVED_GAMES_PATH);

	if (fin) {
		
		std::getline(std::wcin, _command);



		for (int i = 0; i < TOP_SCORE_AMOUNT && !fin.eof(); ++i) {
			fin >> this->topNScore[i];
		}
	}
	fin.close();
}


void Game::loadGame()
{
	//need to be implemented
}


void Game::mainLogic(Point currentPosition, Point newPosition)
{
	// identifying entered position with figures' positions on the board  
	Figure* figureToMove = nullptr;
	
	for (auto figure : *_currentArmy) {
		Point figurePosition = figure->getLocation();

		if (figurePosition == currentPosition) {
			figureToMove = figure;
		}
	}

	if (!figureToMove) {
		_moveCompleted = false;
		
		_logMessage = ErrorInvalidPos3 + _command.substr(0, 2) + L'\n';
		return;
	}

	//castling checking, execution if needed
	if (figureToMove->_firstMove) {
		if (figureToMove->getType() == Type::KING) {
			if (newPosition == Point{ figureToMove->getLocation().x, 2 } ||
				newPosition == Point{ figureToMove->getLocation().x, 6 }) {
				bool moveIsLegal = castling(figureToMove, currentPosition, newPosition);
				
				if (!moveIsLegal) {
					_moveCompleted = false;
					_logMessage = ErrorCastlingString + _command.substr(0, 5) + L'\n';
					return;
				}
				else {
					// deleting data for En passant
					_enPassantFigure = nullptr;
					_firstEnPassantPoint = Point{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

					_moveCompleted = true;
					_logMessage = CastlingPerfomed + _command.substr(0, 5) + L'\n';
					return;
				}
			}
			
		}
	}

	//en passant checking, execution if needed
	if (figureToMove->getType() == Type::PAWN && _enPassantFigure) {
		if (newPosition == _firstEnPassantPoint) {
			if (enPassant(figureToMove, currentPosition, newPosition)) {
				Point secondEnPassantPoint = _enPassantFigure->getLocation();

				_enemyArmy->erase(_enPassantFigure);
				_board[currentPosition.x][currentPosition.y] = nullptr;
				_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = nullptr;
				_board[newPosition.x][newPosition.y] = figureToMove;
				figureToMove->setLocation(newPosition);

				// deleting data for En passant
				_enPassantFigure = nullptr;
				_firstEnPassantPoint = Point{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
				_logMessage = enPassantPerformedString + _command.substr(0, 5) + L'\n';
				_moveCompleted = true;

				return;
			}
			else {
				_logMessage = ErrorenPassantString + _command.substr(0, 5) + L'\n';
				_moveCompleted = false;

				return;
			}
		}
	}
	

	// checking if figureToMove can execute command
	bool moveIsLegal = false;
	auto v_possibleMoves = figureToMove->getPossibleMoves(_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (newPosition == possiblePosition) {
			moveIsLegal = true;
			break;
		}
	}

	if (!moveIsLegal) {
		_moveCompleted = false;
		_logMessage = ErrorMoveIsIllegal + _command.substr(0, 5) + L'\n';

		return;
	}

	// checking if figure's movement doesn't endanger the king
	if (isKingInDanger(figureToMove, currentPosition, newPosition)) {
		_logMessage = ErrorKingIsInDanger + _command.substr(0, 5) + L'\n';
		_moveCompleted = false;

		return;
	}

	// deleting data for En passant
	_enPassantFigure = nullptr;
	_firstEnPassantPoint = Point{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

	//checking for new En passant data
	if (figureToMove->_firstMove) {
		if (figureToMove->getType() == Type::PAWN) {
			int delta = newPosition.x - currentPosition.x;

			if (delta == 2) {
				_enPassantFigure = figureToMove;
				_firstEnPassantPoint = Point{ newPosition.x - 1, newPosition.y };
			}
			else if (delta == -2) {
				_enPassantFigure = figureToMove;
				_firstEnPassantPoint = Point{ newPosition.x + 1, newPosition.y };
			}
		}
	}

	// Removing enemy's figure (if needed) and moving figure on new position
	Figure* enemyFigure = _board[newPosition.x][newPosition.y];

	if (enemyFigure) {
		deletingFigure(enemyFigure);
	}

	_board[currentPosition.x][currentPosition.y] = nullptr;
	_board[newPosition.x][newPosition.y] = figureToMove;
	figureToMove->setLocation(newPosition);
	figureToMove->_firstMove = false;
	_CHECK = false;
	_logMessage = PreviousMoveString + _command.substr(0, 5) + L'\n';

	// checking for promotion
	if (figureToMove->getType() == Type::PAWN && (newPosition.x == 0 || newPosition.x == BOARD_SIZE - 1)) {
		promotion(figureToMove, newPosition);
	}

	_moveCompleted = true;
}


bool Game::castling(Figure* king, Point currentPosition, Point newPosition)
{
	if (!_CHECK) {
		// cheking right rook
		if (newPosition.y > currentPosition.y) {
			Figure* rook = _board[newPosition.x][BOARD_SIZE - 1];

			if (rook && rook->getType() == Type::ROOK && rook->_firstMove) {
				// cheking squares between king and rook
				for (int i = currentPosition.y + 1; i <= newPosition.y; ++i) {
					if (_board[currentPosition.x][i] || isKingInDanger(king, currentPosition, Point{ currentPosition.x, i })) {
						return false;
					}
				}
				// executing castling

				//// king movement
				_board[currentPosition.x][currentPosition.y] = nullptr;
				_board[newPosition.x][newPosition.y] = king;
				king->setLocation(newPosition);

				king->_firstMove = false;

				//// rook movement
				Point rookPosition = rook->getLocation();

				_board[rookPosition.x][rookPosition.y] = nullptr;
				rookPosition.y = newPosition.y - 1;
				_board[rookPosition.x][rookPosition.y] = rook;
				rook->setLocation(rookPosition);

				rook->_firstMove = false;
			}
		}
		else {
			// cheking left rook
			Figure* rook = _board[newPosition.x][0];

			if (rook && rook->getType() == Type::ROOK && rook->_firstMove) {
				// cheking squares between king and rook
				for (int i = currentPosition.y - 1; i > 0; --i) {
					if (_board[currentPosition.x][i]) {
						return false;
					}
				}
				for (int i = currentPosition.y - 1; i > 1; --i) {
					if (isKingInDanger(king, currentPosition, Point{ currentPosition.x, i })) {
						return false;
					}
				}
				// executing castling

				//// king movement
				_board[currentPosition.x][currentPosition.y] = nullptr;
				_board[newPosition.x][newPosition.y] = king;
				king->setLocation(newPosition);

				king->_firstMove = false;

				//// rook movement
				Point rookPosition = rook->getLocation();

				_board[rookPosition.x][rookPosition.y] = nullptr;
				rookPosition.y = newPosition.y + 1;
				_board[rookPosition.x][rookPosition.y] = rook;
				rook->setLocation(rookPosition);

				rook->_firstMove = false;
			}
		}
		return true;
	}

	return false;
}


bool Game::enPassant(Figure* figureToMove, Point currentPosition, Point newPosition)
{
	bool moveIsPossible = false;
	Point secondEnPassantPoint = _enPassantFigure->getLocation();
	int delta = currentPosition.y - secondEnPassantPoint.y;

	if (currentPosition.x == secondEnPassantPoint.x && (delta == 1 || delta == -1)) { 
		// setting board as if move's been executed
		_enemyArmy->erase(_enPassantFigure);
		_board[currentPosition.x][currentPosition.y] = nullptr;
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = nullptr;
		_board[newPosition.x][newPosition.y] = figureToMove;
		figureToMove->setLocation(newPosition);

		// checking for "check"
		moveIsPossible = !isCheck();

		// setting board to previous position
		_board[currentPosition.x][currentPosition.y] = figureToMove;
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = _enPassantFigure;
		_board[newPosition.x][newPosition.y] = nullptr;
		figureToMove->setLocation(currentPosition);

		_enemyArmy->insert(_enPassantFigure);
	}
	
	return moveIsPossible;
}


bool Game::isKingInDanger(Figure* figureToMove, Point currentPosition, Point newPosition)
{
	Figure* enemyFigure = _board[newPosition.x][newPosition.y];

	if (enemyFigure) {
		_enemyArmy->erase(enemyFigure);
	}
	// setting board as if move's been executed
	_board[currentPosition.x][currentPosition.y] = nullptr;
	_board[newPosition.x][newPosition.y] = figureToMove;
	figureToMove->setLocation(newPosition);

	// checking for "check"
	bool inDanger = isCheck();

	// setting board to previous position
	_board[currentPosition.x][currentPosition.y] = figureToMove;
	_board[newPosition.x][newPosition.y] = enemyFigure;
	figureToMove->setLocation(currentPosition);

	if (enemyFigure) {
		_enemyArmy->insert(enemyFigure);
	}

	return inDanger;
}


void Game::promotion(Figure* figureToMove, Point newPosition)
{
	std::wstring previousMoveString = _logMessage;
	Color color = figureToMove->getColor();
	std::wstring figureType;
	Figure* promotedFigure = nullptr;

	std::bitset<BOARD_SIZE>* bit_currentArmy;
	if (_halfTurn % 2) {
		bit_currentArmy = &_bit_whiteArmy;
	}
	else {
		bit_currentArmy = &_bit_blackArmy;
	}

	_logMessage = ChoosePromotionString;

	for (; ;) {
		drawGameField();
		std::wcout << ENTER_COMMAND_STRING;
		std::getline(std::wcin, figureType);

		if (figureType[0] == static_cast<wchar_t>(Type::QUEEN)) {
			promotedFigure = new F_Queen(color, newPosition);

			if (bit_currentArmy->test(bit_F_Queen1)) {
				bit_currentArmy->set(bit_F_Queen2);
			}
			else {
				bit_currentArmy->set(bit_F_Queen1);
			}

			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::BISHOP)) {
			promotedFigure = new F_Bishop(color, newPosition);

			if ((newPosition.x + newPosition.y) % 2) {
				bit_currentArmy->set(bit_F_Bishop1);
			}
			else {
				bit_currentArmy->set(bit_F_Bishop2);
			}
			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::KNIGHT)) {
			promotedFigure = new F_Knight(color, newPosition);

			if (bit_currentArmy->test(bit_F_Knight1)) {
				bit_currentArmy->set(bit_F_Knight2);
			}
			else {
				bit_currentArmy->set(bit_F_Knight1);
			}
			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::ROOK)) {
			promotedFigure = new F_Rook(color, newPosition);

			if (bit_currentArmy->test(bit_F_Rook1)) {
				bit_currentArmy->set(bit_F_Rook2);
			}
			else {
				bit_currentArmy->set(bit_F_Rook1);
			}
			break;
		}
		_logMessage = ErrorPromotionType1 + figureType[0] + ErrorPromotionType2;
	}

	// deleting pawn
	_currentArmy->erase(figureToMove);
	delete figureToMove;
	_pawnQuantity -= 1;

	// setting new figure
	_board[newPosition.x][newPosition.y] = promotedFigure;
	_currentArmy->insert(promotedFigure);
	
	_logMessage = previousMoveString;
}


void Game::deletingFigure(Figure* enemyFigure)
{
	_enemyArmy->erase(enemyFigure);
	Type type = enemyFigure->getType();
	Point location = enemyFigure->getLocation();
	
	std::bitset<BOARD_SIZE>* bit_enemyArmy;
	if (_halfTurn % 2) {
		bit_enemyArmy = &_bit_blackArmy;
	}
	else {
		bit_enemyArmy = &_bit_whiteArmy;
	}

	// updating bitset considering type of deleted figure
	switch (type) {
		case Type::QUEEN:
			if (bit_enemyArmy->test(bit_F_Queen2)) {
				bit_enemyArmy->reset(bit_F_Queen2);
			}
			else {
				bit_enemyArmy->reset(bit_F_Queen1);
			}
			break;
		case Type::BISHOP:
			if ((location.x + location.y) % 2) {
				bit_enemyArmy->reset(bit_F_Bishop1);
			}
			else {
				bit_enemyArmy->reset(bit_F_Bishop2);
			}
			break;
		case Type::KNIGHT:
			if (bit_enemyArmy->test(bit_F_Knight2)) {
				bit_enemyArmy->reset(bit_F_Knight2);
			}
			else {
				bit_enemyArmy->reset(bit_F_Knight1);
			}
			break;
		case Type::ROOK:
			if (bit_enemyArmy->test(bit_F_Rook2)) {
				bit_enemyArmy->reset(bit_F_Rook2);
			}
			else {
				bit_enemyArmy->reset(bit_F_Rook1);
			}
			break;
		case Type::PAWN:
			_pawnQuantity -= 1;
			break;
		default:
			break;
	}
	
	delete enemyFigure;
}


void Game::customGame()
{
	// resetting armies' bitsets and pawn quantity
	_bit_whiteArmy.reset();
	_bit_blackArmy.reset();
	_pawnQuantity = 0;

	// deleting current figures
	for (auto figure : *_whiteArmy) {
		delete figure;
	}
	_whiteArmy->clear();

	for (auto figure : *_blackArmy) {
		delete figure;
	}
	_blackArmy->clear();

	// Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	// local variables
	std::wstring col_type_loc;
	Point location;
	Figure* newFigure = nullptr;
	Color color;
	bool WhiteKing = false;
	bool BlackKing = false;
	_logMessage = EnteringCustomString;

	// main block
	while (true) {
		drawGameField();
		std::getline(std::wcin, col_type_loc);

		// Cheking "QUIT", "DONE" commands
		if (col_type_loc[0] == L'Q') {
			newGame();
			return;
		}
		else if (col_type_loc[0] == L'D') {
			// checking for presence of two kings
			if (!WhiteKing || !BlackKing) {
				_logMessage = EnteringCustomString + ErrorPlaceKingsString;
				continue;
			}
			else {
				// setting side to make move
				_logMessage = EnteringCustomString + ChooseSideToMoveString;
				while (true) {
					drawGameField();
					std::getline(std::wcin, col_type_loc);
					if (col_type_loc[0] == static_cast<wchar_t>(Color::WHITE)) {
						_halfTurn = 0;
						break;
					}
					else if (col_type_loc[0] == static_cast<wchar_t>(Color::BLACK)) {
						_halfTurn = 1;
						break;
					}
				}
				_logMessage = NewCustomGameString;
				return;
			}			
		}

		// checking parameters for Move instruction, at least 5 symbols are required, e.g. "A2-A4", "B7 B4 "
		if (col_type_loc.size() < 4) {
			_logMessage = EnteringCustomString + ErrorDataCustomString;
			continue;
		}

		//setting location, e.g "A8" == Point(0,0),"B3" == Point(5,1)
		wchar_t capitalLetter = L'A';
		bool firstCoord = false;
		bool secondCoord = false;

		for (int i = 0, j = BOARD_SIZE - 1; i < BOARD_SIZE; ++i) {
			if (col_type_loc[2] == capitalLetter) {
				location.y = i;
				firstCoord = true;
			}

			if (col_type_loc[3] == static_cast<wchar_t>(i + 49)) {
				location.x = j - i;
				secondCoord = true;
			}
			capitalLetter += 1;
		}

		if (!firstCoord || !secondCoord) {
			_logMessage = EnteringCustomString + ErrorLocCustomString +
				col_type_loc.substr(2, 2) + L'\n';
			continue;
		}
		else if (_board[location.x][location.y]) {
			_logMessage = EnteringCustomString + ErrorLocOccupiedCustomString +
				col_type_loc.substr(2, 2) + L'\n';
			continue;
		}

		//setting color
		if (col_type_loc[0] == static_cast<wchar_t>(Color::WHITE)) {
			color = Color::WHITE;

			//setting type, creating new figure, adding figure to white army and setting army's bitset
			switch (col_type_loc[1]) {
				case static_cast<wchar_t>(Type::KING) :
					newFigure = new F_King(color, location);
					_whiteArmy->insert(newFigure);

					WhiteKing = true;
					_WKing = newFigure;
					break;
					
				case static_cast<wchar_t>(Type::QUEEN) :
					newFigure = new F_Queen(color, location);
					_whiteArmy->insert(newFigure);

					if (_bit_whiteArmy.test(bit_F_Queen1)) {
						_bit_whiteArmy.set(bit_F_Queen2);
					}
					else {
						_bit_whiteArmy.set(bit_F_Queen1);
					}
					break;

				case static_cast<wchar_t>(Type::BISHOP) :
					newFigure = new F_Bishop(color, location);
					_whiteArmy->insert(newFigure);

					if ((location.x + location.y) % 2) {
						_bit_whiteArmy.set(bit_F_Bishop1);
					}
					else {
						_bit_whiteArmy.set(bit_F_Bishop2);
					}
					break;

				case static_cast<wchar_t>(Type::KNIGHT) :
					newFigure = new F_Knight(color, location);
					_whiteArmy->insert(newFigure);

					if (_bit_whiteArmy.test(bit_F_Knight1)) {
						_bit_whiteArmy.set(bit_F_Knight2);
					}
					else {
						_bit_whiteArmy.set(bit_F_Knight1);
					}
					break;

				case static_cast<wchar_t>(Type::ROOK) :
					newFigure = new F_Rook(color, location);
					_whiteArmy->insert(newFigure);

					if (_bit_whiteArmy.test(bit_F_Rook1)) {
						_bit_whiteArmy.set(bit_F_Rook2);
					}
					else {
						_bit_whiteArmy.set(bit_F_Rook1);
					}
					break;

				case static_cast<wchar_t>(Type::PAWN) :
					newFigure = new F_Pawn(color, location);
					_whiteArmy->insert(newFigure);
					break;

				default:
					_logMessage = EnteringCustomString + ErrorTypeCustomString +
						col_type_loc.substr(0, 2) + L'\n';
					continue;
			}
		}
		else if (col_type_loc[0] == static_cast<wchar_t>(Color::BLACK)) {
			color = Color::BLACK;

			//setting type, creating new figure, adding figure to black army and setting army's bitset
			switch (col_type_loc[1]) {
				case static_cast<wchar_t>(Type::KING) :
					newFigure = new F_King(color, location);
					_blackArmy->insert(newFigure);

					BlackKing = true;
					_BKing = newFigure;
					break;
					
				case static_cast<wchar_t>(Type::QUEEN) :
					newFigure = new F_Queen(color, location);
					_blackArmy->insert(newFigure);

					if (_bit_blackArmy.test(bit_F_Queen1)) {
						_bit_blackArmy.set(bit_F_Queen2);
					}
					else {
						_bit_blackArmy.set(bit_F_Queen1);
					}
					break;

				case static_cast<wchar_t>(Type::BISHOP) :
					newFigure = new F_Bishop(color, location);
					_blackArmy->insert(newFigure);

					if ((location.x + location.y) % 2) {
						_bit_blackArmy.set(bit_F_Bishop1);
					}
					else {
						_bit_blackArmy.set(bit_F_Bishop2);
					}
					break;

				case static_cast<wchar_t>(Type::KNIGHT) :
					newFigure = new F_Knight(color, location);
					_blackArmy->insert(newFigure);

					if (_bit_blackArmy.test(bit_F_Knight1)) {
						_bit_blackArmy.set(bit_F_Knight2);
					}
					else {
						_bit_blackArmy.set(bit_F_Knight1);
					}
					break;

				case static_cast<wchar_t>(Type::ROOK) :
					newFigure = new F_Rook(color, location);
					_blackArmy->insert(newFigure);

					if (_bit_blackArmy.test(bit_F_Rook1)) {
						_bit_blackArmy.set(bit_F_Rook2);
					}
					else {
						_bit_blackArmy.set(bit_F_Rook1);
					}
					break;

				case static_cast<wchar_t>(Type::PAWN) :
					newFigure = new F_Pawn(color, location);
					_blackArmy->insert(newFigure);
					_pawnQuantity += 1;
					break;

				default:
					_logMessage = EnteringCustomString + ErrorTypeCustomString +
						col_type_loc.substr(0, 2) + L'\n';
					continue;
			}
		}
		else {
			_logMessage = EnteringCustomString + ErrorColorCustomString +
			col_type_loc.substr(0, 2) + L'\n';
			continue;
		}

		_board[location.x][location.y] = newFigure;

		//setting first move state
		if (col_type_loc[5] != L'1') {
			newFigure->_firstMove = false;
		}

		_logMessage = EnteringCustomString + FigureIsPlacedString +
			col_type_loc.substr(0, 4) + L'\n';
	}
}


void Game::gameLoop()
{
	while (!_gameOver) {
		_halfTurn += 1;

		// updating pointers for quick access
		if (_halfTurn % 2) {
			_currentArmy = _whiteArmy;
			_enemyArmy = _blackArmy;
			_activeKing = _WKing;
		}
		else {
			_currentArmy = _blackArmy;
			_enemyArmy = _whiteArmy;
			_activeKing = _BKing;
		}

		if (isCheck()) {
			_CHECK = true;
			if (isCheckmate()) {
				_gameOver = true;
				_moveCompleted = true;
			}
		}
		else if (isDraw()) {
			_gameOver = true;
			_moveCompleted = true;
		}

		while (!_moveCompleted) {
			drawGameField();
			input();
		}

		_moveCompleted = false;
		
	}

	drawGameField();
}
