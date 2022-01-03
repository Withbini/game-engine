#include "ShipGame.hpp"

int main(int argc,char* argv[])
{
	//Game game;
	ShipGame game;
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
