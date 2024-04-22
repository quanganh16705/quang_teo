#include "header/Game.h"
#include "header/GameOver.h"
#include "header/MainMenu.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (initWindow())
	{
		MainMenu menu;
		GameOver gameOver;
		if (menu.show())
		{
			do
			{
				Game *game = new Game();
				game->run();
				if (game->isQuit())
				{
					delete game;
					break;
				}
				delete game;
			} while (gameOver.show());
		}
	}

	closeWindow();
	return 0;
}