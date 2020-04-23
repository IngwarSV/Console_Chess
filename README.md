# Console_Chess
Implemented:

1. Players may interact with the application using command line instructions. For example:
	a. Restart game - using "N" / "n";
	b. Move - using "A2 A4" / "A2-A4" (third symbol is free to enter, within reasonable limits);

2. The application validates all moves (if a player wants to make a move that is not allowed by chess rules, 
   the application blocks such attempt and shows corresponding notification.
3. The application correctly handles all chess rules:
	a. castling;
	b. check;
	c. checkmate;
	d. draw (stalemate, impossibility of checkmate (two kings left, king and knight versus king,
		king with/without bishop versus king and bishop/bishops on the same color);
	e. en passant move;
	f. promotion (to Queen, Bishop, Knight, Rook).
 4. Saving games (app creates directory Saved Games) with all data (including data for castling, en passant).
 5. Loading saved games (including data for castling, en passant).
 6. Google tests for game logic.

IDE: Microsoft Visual Studio 2019 Community edition
