#include "openglGame.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "Asteroid.hpp"
#include "BGSpriteComponent.hpp"
#include "openglRenderer.hpp"
#include "Ship2.hpp"

openglGame::openglGame()
{
	stbi_set_flip_vertically_on_load(true);
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