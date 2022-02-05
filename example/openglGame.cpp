#include "openglGame.hpp"
#include "Asteroid.hpp"
#include "openglRenderer.hpp"
#include "Ship2.hpp"

openglGame::openglGame()
{
}

openglGame::~openglGame()
{
}

bool openglGame::Initialize()
{
	mRenderer = new openglRenderer(this);
	if (!mRenderer->Initialize((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}
	LoadData();
	return true;
}
void openglGame::LoadData()
{
	mShip = new Ship2(this);
	mShip->SetPosition(Vector3(0.f, 0.0f,0.0f));
	mShip->SetScale(1.5f);

	const int numAsteriod = 20;
	for (int i = 0; i < numAsteriod; ++i)
	{
		new Asteroid(this);
	}
}