#include "ShipGame.hpp"
#include "AsteroidGame.hpp"

int main(int argc,char* argv[])
{
	//Game game;
	//ShipGame game;
	AsteroidGame game;
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
