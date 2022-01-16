#include "ShipGame.hpp"
#include "AsteroidGame.hpp"
#include "openglGame.hpp"

int main(int argc,char* argv[])
{
	//Game game;
	//ShipGame game;
	//AsteroidGame game;
	//Game game;
	openglGame game;
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
