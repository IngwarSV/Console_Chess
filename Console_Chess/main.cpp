

#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "Game.h"




int main() {

	_setmode(_fileno(stdout), _O_WTEXT);

	Game game;
	game.gameLoop();


	
	return 0;
}