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
				_totalGameField[i][j] = (j % 2) ? L"  " : L"\u2502";
			}
			else {
				_totalGameField[i][j] = (j % 2) ? L"\u2500\u2500" : L"\u253C";
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
	_enPassantFigure = nullptr; // pawn that just made two-squares move
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
	
	// Setting console font
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");
	if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi)) {
		std::cout << "SetCurrentConsoleFontEx failed with error " << GetLastError() << std::endl;
	}

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


void Game::drawGameField()
{
	// updating totalGameField considering situation on the board
	for (int i = 1, k = 0; i < GAME_FIELD_SIZE; i += 2, k += 1) {
		for (int j = 1, l = 0; j < GAME_FIELD_SIZE; j += 2, l += 1) {
			_totalGameField[i][j] = (_board[k][l]) ?
				_board[k][l]->getFigureName() : L"  ";
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
	
	(_halfTurn % 2) ? 
		std::wcout << WHITE_MOVE_STRING : std::wcout << BLACK_MOVE_STRING;

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

	// Cheking "New Game", "Load Game", "Save Game", "Custom Game" commands
	if (_command[0] == L'N') {
		newGame();
		_moveCompleted = true;

		return;
	}
	if (_command[0] == L'L') {
		loadGame();

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

	for (int i = 0, maxXCoord = BOARD_SIZE - 1; i < BOARD_SIZE; ++i) {
		if (_command[0] == capitalLetter) {
			currentPosition.y = i;
			flag1 = false;
		}
		
		if (_command[1] == static_cast<wchar_t>(i + '1')) {
			currentPosition.x = maxXCoord - i;
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

		if (_command[4] == static_cast<wchar_t>(i + '1')) {
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
	fs::create_directory(SAVED_GAMES_DIR);
	std::wstring fileName;
	_logMessage = SaveGameAsString;

	drawGameField();

	std::getline(std::wcin, fileName);

	fileName += L".txt";
	//deleting whitespaces if needed
	fileName.erase(remove_if(fileName.begin(), fileName.end(), isspace), fileName.end());

	std::wofstream save(SAVED_GAMES_DIR + L'\\' + fileName);

	if (save) {
		// saving _halfTurn
		save << _halfTurn << L'\n';

		// saving "en passant" actions 
		//// location of the pawn, that just made two-square move
		Point secondEnPassantPoint{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
		
		if (_enPassantFigure) {
			secondEnPassantPoint = _enPassantFigure->getLocation();
		}
		
		//// _firstEnPassantPoint - square that was skipped by the pawn
		save << secondEnPassantPoint.x << L' ' << secondEnPassantPoint.y << L'\n'
			<< _firstEnPassantPoint.x << L' ' << _firstEnPassantPoint.y << L'\n';
		
		// saving figures in std::wstring e.g. "WKA21" - white king, location A2, first move - true;
		for (auto figure : *_whiteArmy) {
			Point location = figure->getLocation();
			int xCoord = BOARD_SIZE - location.x;
			wchar_t yCoord = static_cast<wchar_t>(location.y + 'A');

			save << figure->getFigureName() << yCoord << xCoord << figure->_firstMove << ' ';
		}

		save << '\n';

		for (auto figure : *_blackArmy) {
			Point location = figure->getLocation();
			int xCoord = BOARD_SIZE - location.x;
			wchar_t yCoord = static_cast<wchar_t>(location.y + 'A');

			save << figure->getFigureName() << yCoord << xCoord << figure->_firstMove << ' ';
		}
		
		_logMessage = SuccessSaveGameString + fileName + L'\n';
	}
	else {
		_logMessage = ErrorSaveGameString + fileName + L'\n';
	}
	
	save.close();
}


void Game::loadGame()
{
	// checking whether SavedGames directory exists
	if (!fs::is_directory(SAVED_GAMES_DIR) || fs::is_empty(SAVED_GAMES_DIR)) {
		_logMessage = ErrorLoadGameString;
		_moveCompleted = false;

		return;
	}
	
	std::wstring fileName;
	_logMessage = ChooseLoadFileString;
	
	drawGameField();

	// outputing existing files in SavedGames directory
	for (auto& files : fs::directory_iterator(SAVED_GAMES_DIR)) {
		std::wcout << L'\t' << files.path() << L'\n';
	}
	std::wcout << L'\t';

	// entering the selected filename
	std::getline(std::wcin, fileName);
	fileName += L".txt";

	std::wifstream load(SAVED_GAMES_DIR + L'\\' + fileName);
	if (load) {
		// deleting existing game data to load saved game
		clearData();

		// loading _halfTurn
		load >> _halfTurn;
		_halfTurn -= 1;

		// loading "en passant" actions 
		//// location of the pawn, that just made two-squares move
		Point secondEnPassantPoint; 
		load >> secondEnPassantPoint.x >> secondEnPassantPoint.y;
		//// _firstEnPassantPoint - square that was skipped by the pawn
		load >> _firstEnPassantPoint.x >> _firstEnPassantPoint.y;

		//parsing strings into figure's data
		std::wstring col_type_loc;
		
		while (load) {
			load >> col_type_loc;
			//std::getline(load, col_type_loc);
			parseFigureDataString(col_type_loc);
		}

		//// setting pointer to figure, that has just made two-squares move (or to nullprt)
		_enPassantFigure = (secondEnPassantPoint != Point{ BOARD_SIZE, BOARD_SIZE }) ?
			_board[secondEnPassantPoint.x][secondEnPassantPoint.y] : nullptr;
	}
	else {
		_logMessage = NoSuchLoadFileString + fileName + L'\n';
		_moveCompleted = false;

		return;
	}

	load.close();
	_logMessage = LoadGameSuccessString + fileName + L'\n';
	_moveCompleted = true;
}


void Game::customGame()
{
	std::wstring col_type_loc;
	Point location;
	_logMessage = EnteringCustomString;

	// deleting existing game data to customize new game
	clearData();

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

		// checking parameters for Move instruction, at least 5 symbols are required, e.g. "A2-A4", "B7 B4 "
		if (col_type_loc.size() < 4) {
			_logMessage = EnteringCustomString + ErrorDataCustomString;

			continue;
		}

		parseFigureDataString(col_type_loc);
	}

}


void Game::mainLogic(Point currentPosition, Point newPosition)
{
	// identifying entered position with figures' positions on the board  
	Figure* figureToMove = _board[currentPosition.x][currentPosition.y];
	
	if (!figureToMove) {
		_moveCompleted = false;
		_logMessage = ErrorInvalidPos3 + _command.substr(0, 2) + L'\n';

		return;
	}

	//castling checking, execution if true
	if (castling(figureToMove, currentPosition, newPosition)) {
		// king movement
		_board[currentPosition.x][currentPosition.y] = nullptr;
		_board[newPosition.x][newPosition.y] = figureToMove;
		figureToMove->setLocation(newPosition);
		figureToMove->_firstMove = false;

		// rook movement
		Point rookPosition;
		Point rookNewPosition;
		if (newPosition.y > currentPosition.y) {
			rookPosition = Point{ currentPosition.x, BOARD_SIZE - 1 };
			rookNewPosition = Point{ currentPosition.x, newPosition.y - 1 };
		}
		else {
			rookPosition = Point{ currentPosition.x, 0 };
			rookNewPosition = Point{ currentPosition.x, newPosition.y + 1 };
		}
		Figure* rook = _board[rookPosition.x][rookPosition.y];

		_board[rookPosition.x][rookPosition.y] = nullptr;
		_board[rookNewPosition.x][rookNewPosition.y] = rook;
		rook->setLocation(rookNewPosition);
		rook->_firstMove = false;

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_firstEnPassantPoint = Point{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

		_logMessage = CastlingPerfomed + _command.substr(0, 5) + L'\n';
		_moveCompleted = true;

		return;
	}

	
	// en passant checking, execution if true
	if (enPassant(figureToMove, currentPosition, newPosition)) {
		Point secondEnPassantPoint = _enPassantFigure->getLocation();

		deletingFigure(_enPassantFigure);
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
	if ((king->getType() == Type::KING) && !_CHECK) {
		if (king->_firstMove) {
			if (newPosition == Point{ king->getLocation().x, 2 } || 
				newPosition == Point{ king->getLocation().x, 6 }) {
				
				// cheking if squares king has to move are empty
				int delta = (newPosition.y - currentPosition.y) / 2;
				Point square1{ currentPosition.x, currentPosition.y + delta };
				Point square2{ currentPosition.x, currentPosition.y + delta + delta};
				if (!_board[currentPosition.x][square1.y] && !_board[currentPosition.x][square2.y]) {
					
					// cheking if squares king to move are not under attack
					if (!isKingInDanger(king, currentPosition, square1) && !isKingInDanger(king, currentPosition, square2)) {
						
						// choosing kingside or queenside rook
						Figure* rook = nullptr;
						if (delta > 0) {
							rook = _board[currentPosition.x][BOARD_SIZE - 1];
						}
						else {
							rook = _board[currentPosition.x][0];
							// cheking if square queenside rook has to move is empty
							if (_board[currentPosition.x][1]) {
								return false;
							}
						}

						// cheking rook
						if (rook && rook->getType() == Type::ROOK && rook->_firstMove) {
							return true;
						}
					}
				}
			}
		}
	}
	
	return false;
}


bool Game::enPassant(Figure* figureToMove, Point currentPosition, Point newPosition)
{
	bool moveIsPossible = false;
	
	if (figureToMove->getType() == Type::PAWN && _enPassantFigure) {
		if (newPosition == _firstEnPassantPoint) {
			// location of the pawn, that just made two-squares move
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
				_enemyArmy->insert(_enPassantFigure);
				_board[currentPosition.x][currentPosition.y] = figureToMove;
				_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = _enPassantFigure;
				_board[newPosition.x][newPosition.y] = nullptr;
				figureToMove->setLocation(currentPosition);
			}
		}
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
	bit_currentArmy = (_halfTurn % 2) ? &_bit_whiteArmy : &_bit_blackArmy;
	
	_logMessage = ChoosePromotionString;

	while (true) {
		drawGameField();
		std::wcout << ENTER_COMMAND_STRING;

		std::getline(std::wcin, figureType);

		if (figureType[0] == static_cast<wchar_t>(Type::QUEEN)) {
			promotedFigure = new F_Queen(color, newPosition);

			(bit_currentArmy->test(bit_F_Queen1)) ? 
				bit_currentArmy->set(bit_F_Queen2) : bit_currentArmy->set(bit_F_Queen1);

			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::BISHOP)) {
			promotedFigure = new F_Bishop(color, newPosition);

			((newPosition.x + newPosition.y) % 2) ?
				bit_currentArmy->set(bit_F_Bishop1) : bit_currentArmy->set(bit_F_Bishop2);

			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::KNIGHT)) {
			promotedFigure = new F_Knight(color, newPosition);

			(bit_currentArmy->test(bit_F_Knight1)) ?
				bit_currentArmy->set(bit_F_Knight2) : bit_currentArmy->set(bit_F_Knight1);

			break;
		}
		else if (figureType[0] == static_cast<wchar_t>(Type::ROOK)) {
			promotedFigure = new F_Rook(color, newPosition);

			(bit_currentArmy->test(bit_F_Rook1)) ?
				bit_currentArmy->set(bit_F_Rook2) : bit_currentArmy->set(bit_F_Rook1);
			
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
	Type type = enemyFigure->getType();
	Point location = enemyFigure->getLocation();
	std::bitset<BOARD_SIZE>* bit_enemyArmy;

	bit_enemyArmy = (_halfTurn % 2) ?
		 &_bit_blackArmy : bit_enemyArmy = &_bit_whiteArmy;
	
	// updating bitset considering type of deleted figure
	switch (type) {

		case Type::QUEEN:
			(bit_enemyArmy->test(bit_F_Queen2)) ?
				bit_enemyArmy->reset(bit_F_Queen2) : bit_enemyArmy->reset(bit_F_Queen1);
			
			break;

		case Type::BISHOP:
			((location.x + location.y) % 2) ?
				bit_enemyArmy->reset(bit_F_Bishop1) : bit_enemyArmy->reset(bit_F_Bishop2);
			
			break;

		case Type::KNIGHT:
			(bit_enemyArmy->test(bit_F_Knight2)) ?
				bit_enemyArmy->reset(bit_F_Knight2) : bit_enemyArmy->reset(bit_F_Knight1);
			
			break;

		case Type::ROOK:
			(bit_enemyArmy->test(bit_F_Rook2)) ?
				bit_enemyArmy->reset(bit_F_Rook2) : bit_enemyArmy->reset(bit_F_Rook1);
			
			break;

		case Type::PAWN:
			_pawnQuantity -= 1;

			break;

		default:
			break;
	}
	
	_enemyArmy->erase(enemyFigure);
	delete enemyFigure;
}


void Game::clearData()
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
}


void Game::parseFigureDataString(std::wstring col_type_loc)
{
	Point location;
	Figure* newFigure = nullptr;
	Color color;

	//setting location, e.g "A8" == Point(0,0),"B3" == Point(5,1)
	wchar_t capitalLetter = L'A';
	bool firstCoord = false;
	bool secondCoord = false;

	for (int i = 0, maxXCoord = BOARD_SIZE - 1; i < BOARD_SIZE; ++i) {
		if (col_type_loc[2] == capitalLetter) {
			location.y = i;
			firstCoord = true;
		}

		if (col_type_loc[3] == static_cast<wchar_t>(i + L'1')) {
			location.x = maxXCoord - i;
			secondCoord = true;
		}
		capitalLetter += 1;
	}

	if (!firstCoord || !secondCoord) {
		_logMessage = EnteringCustomString + ErrorLocCustomString +
			col_type_loc.substr(2, 2) + L'\n';
		return;
	}
	else if (_board[location.x][location.y]) {
		_logMessage = EnteringCustomString + ErrorLocOccupiedCustomString +
			col_type_loc.substr(2, 2) + L'\n';
		return;
	}

	//setting color
	if (col_type_loc[0] == static_cast<wchar_t>(Color::WHITE)) {
		color = Color::WHITE;

		//setting type, creating new figure, adding figure to white army and setting army's bitset
		switch (col_type_loc[1]) {

			case static_cast<wchar_t>(Type::KING) :
				newFigure = new F_King(color, location);
				_whiteArmy->insert(newFigure);
				_WKing = newFigure;

				break;
					
			case static_cast<wchar_t>(Type::QUEEN) :
				newFigure = new F_Queen(color, location);
				_whiteArmy->insert(newFigure);

				(_bit_whiteArmy.test(bit_F_Queen1)) ? 
					_bit_whiteArmy.set(bit_F_Queen2) : _bit_whiteArmy.set(bit_F_Queen1);

				break;

			case static_cast<wchar_t>(Type::BISHOP) :
				newFigure = new F_Bishop(color, location);
				_whiteArmy->insert(newFigure);

				((location.x + location.y) % 2) ?
					_bit_whiteArmy.set(bit_F_Bishop1) : _bit_whiteArmy.set(bit_F_Bishop2);

				break;

			case static_cast<wchar_t>(Type::KNIGHT) :
				newFigure = new F_Knight(color, location);
				_whiteArmy->insert(newFigure);

				(_bit_whiteArmy.test(bit_F_Knight1)) ?
					_bit_whiteArmy.set(bit_F_Knight2) : _bit_whiteArmy.set(bit_F_Knight1);

				break;

			case static_cast<wchar_t>(Type::ROOK) :
				newFigure = new F_Rook(color, location);
				_whiteArmy->insert(newFigure);

				(_bit_whiteArmy.test(bit_F_Rook1)) ?
					_bit_whiteArmy.set(bit_F_Rook2) : _bit_whiteArmy.set(bit_F_Rook1);
				
				break;

			case static_cast<wchar_t>(Type::PAWN) :
				newFigure = new F_Pawn(color, location);
				_whiteArmy->insert(newFigure);
				_pawnQuantity += 1;

				break;

			default:
				_logMessage = EnteringCustomString + ErrorTypeCustomString +
					col_type_loc.substr(0, 2) + L'\n';

				return;
		}

		//setting first move state
		if (col_type_loc[4] != L'1') {
			newFigure->_firstMove = false;
		}

		_board[location.x][location.y] = newFigure;

		_logMessage = EnteringCustomString + FigureIsPlacedString +
			col_type_loc.substr(0, 4) + L'\n';

		return;
	}
	else if (col_type_loc[0] == static_cast<wchar_t>(Color::BLACK)) {
		color = Color::BLACK;

		//setting type, creating new figure, adding figure to black army and setting army's bitset
		switch (col_type_loc[1]) {

			case static_cast<wchar_t>(Type::KING) :
				newFigure = new F_King(color, location);
				_blackArmy->insert(newFigure);
				_BKing = newFigure;

				break;
					
			case static_cast<wchar_t>(Type::QUEEN) :
				newFigure = new F_Queen(color, location);
				_blackArmy->insert(newFigure);

				(_bit_blackArmy.test(bit_F_Queen1)) ? 
					_bit_blackArmy.set(bit_F_Queen2) : _bit_blackArmy.set(bit_F_Queen1);
				
				break;

			case static_cast<wchar_t>(Type::BISHOP) :
				newFigure = new F_Bishop(color, location);
				_blackArmy->insert(newFigure);

				((location.x + location.y) % 2) ?
					_bit_blackArmy.set(bit_F_Bishop1) : _bit_blackArmy.set(bit_F_Bishop2);
				
				break;

			case static_cast<wchar_t>(Type::KNIGHT) :
				newFigure = new F_Knight(color, location);
				_blackArmy->insert(newFigure);

				(_bit_blackArmy.test(bit_F_Knight1)) ?
					_bit_blackArmy.set(bit_F_Knight2) : _bit_blackArmy.set(bit_F_Knight1);
				
				break;

			case static_cast<wchar_t>(Type::ROOK) :
				newFigure = new F_Rook(color, location);
				_blackArmy->insert(newFigure);

				(_bit_blackArmy.test(bit_F_Rook1)) ?
					_bit_blackArmy.set(bit_F_Rook2) : _bit_blackArmy.set(bit_F_Rook1);
				
				break;

			case static_cast<wchar_t>(Type::PAWN) :
				newFigure = new F_Pawn(color, location);
				_blackArmy->insert(newFigure);
				_pawnQuantity += 1;

				break;

			default:
				_logMessage = EnteringCustomString + ErrorTypeCustomString +
					col_type_loc.substr(0, 2) + L'\n';

				break;
		}

		//setting first move state
		if (col_type_loc[4] != L'1') {
			newFigure->_firstMove = false;
		}

		_board[location.x][location.y] = newFigure;

		_logMessage = EnteringCustomString + FigureIsPlacedString +
			col_type_loc.substr(0, 4) + L'\n';

		return;
	}
	else {
		_logMessage = EnteringCustomString + ErrorColorCustomString +
		col_type_loc.substr(0, 2) + L'\n';

		return;
	}
}


void Game::loadGameDataString(std::wstring dataString) // create new custom Game from string, for testing
{
	std::wistringstream load(dataString);

	// deleting existing game data to load saved game
	clearData();

	// loading _halfTurn
	load >> _halfTurn;
	
	// loading "en passant" actions 
	//// location of the pawn, that just made two squares move
	Point secondEnPassantPoint;
	load >> secondEnPassantPoint.x >> secondEnPassantPoint.y;
	//// _firstEnPassantPoint - square that was skipped by the pawn
	load >> _firstEnPassantPoint.x >> _firstEnPassantPoint.y;
	
	//parsing strings into figure's data
	std::wstring col_type_loc;

	while (load) {
		load >> col_type_loc;
		parseFigureDataString(col_type_loc);
	}

	// setting pointers for quick access
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

	//// setting pointer to the pawn, that has just made two-squares move (or nullprt)
	_enPassantFigure = (secondEnPassantPoint != Point{ BOARD_SIZE, BOARD_SIZE }) ?
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] : nullptr;

	_CHECK = isCheck();
}


// getters for testing

Figure* Game::getBoard(Point point) const {
	return _board[point.x][point.y];
}

const std::unordered_set<Figure*>* Game::getWhiteArmy() const {
	return _whiteArmy;
}

const std::unordered_set<Figure*>* Game::getBlackArmy() const {
	return _blackArmy;
}

Figure* Game::getActiveKing() const {
	return _activeKing;
}

const std::bitset<BOARD_SIZE>& Game::getWArmyBit() const {
	return _bit_whiteArmy;
}

const std::bitset<BOARD_SIZE>& Game::getBArmyBit() const {
	return _bit_blackArmy;
}

const int Game::getPawnQuantity() const {
	return _pawnQuantity;
}

const std::unordered_set<Figure*>* Game::getCurrentArmy() const {
	return _currentArmy;
}

const std::unordered_set<Figure*>* Game::getEnemyArmy() const {
	return _enemyArmy;
}

const Figure* Game::getEnPassantFigure() const {
	return _enPassantFigure;
}

const Point Game::getFirstEnPassantPoint() const {
	return _firstEnPassantPoint;
}

const int Game::getHalfTurn() const {
	return _halfTurn;
}

const bool Game::getCHECKStatus() const {
	return _CHECK;
}

const bool Game::getGameOverStatus() const {
	return _gameOver;
}

const bool Game::getMoveCompletedStatus() const {
	return _moveCompleted;
}

const std::wstring& Game::getCurrentCommand() const {
	return _command;
}

const std::wstring& Game::getLogMessage() const {
	return _logMessage;
}
