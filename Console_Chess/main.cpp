

#include <iostream>
#include <fcntl.h>
#include <io.h>
//#include <stdio.h>

#include "Game.h"




int main() {

	//_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_WTEXT);

	Game game;
	game.drawGameField();









	return 0;
}