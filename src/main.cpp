#include "ShipGame.hpp"
#include "AsteroidGame.hpp"
#include "openglGame.hpp"
#include "3dGame.hpp"
int main(int argc,char* argv[])
{
	//Game game;
	//ShipGame game;
	//AsteroidGame game;
	//Game game;
	//openglGame game;
	GL3DGame game;
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}