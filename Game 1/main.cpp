#include "Game.h"

int main()
{
	srand(time(0));

	Game game;

	// Game loop 
	while (game.run() && !game.getEndGame())
	{
		game.update();
		game.render();
	}

	return 0;
}