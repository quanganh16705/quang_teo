#include "header/Game.h"
#include "header/GameOver.h"
#include "header/MainMenu.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (initWindow())
	{
		MainMenu menu;

		if (menu.show())
		{
			Game *game=new Game();
			game->run();
			delete game;
			GameOver gameOver;
			while (gameOver.show())
			{
				Game *game=new Game();
				game->run();
				if(game->isQuit()) {
					delete game;
					break;
				}
				delete game;
			}
		}
	}
	closeWindow();
	return 0;
}