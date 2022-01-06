#include "AsteroidGame.hpp"
#include "Asteroid.hpp"
#include "BGSpriteComponent.hpp"
#include "Ship2.hpp"

void AsteroidGame::LoadData()
{
	mShip = new Ship2(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);
	
	const int numAsteriod = 20;
	for(int i=0;i< numAsteriod;++i)
	{
		auto* asteroid = new Asteroid(this);
	}

	auto*tmp = new Actor(this);
	tmp->SetPosition(Vector2(WINDOW_WIDGHT/2.f, WINDOW_HEIGHT/2.f));
	auto*bg = new BGSpriteComponent(tmp);

	bg->SetScreenSize(Vector2(WINDOW_WIDGHT, WINDOW_HEIGHT));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
}

void AsteroidGame::ProcessInput()
{
	Game::ProcessInput();
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	mShip->ProcessKeyboard(state);
}
