#include "game.hpp"
<<<<<<< HEAD
#include "ShipGame.hpp"

int main(int argc,char* argv[])
{
	//Game game;
	ShipGame game;
=======

int main(int argc,char* argv[])
{
	Game game;
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
