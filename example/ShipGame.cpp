#include "ShipGame.hpp"
#include "BGSpriteComponent.hpp"
#include "Ship.hpp"

void ShipGame::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector3(100.0f, 384.0f,0.f));
	mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector3(512.0f, 384.0f,0.f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<Texture*> bgtexs = {
		GetRenderer()->GetTexture("Assets/Farback01.png"),
		GetRenderer()->GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetRenderer()->GetTexture("Assets/Stars.png"),
		GetRenderer()->GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void ShipGame::ProcessInput()
{
	Game::ProcessInput();
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	mShip->ProcessKeyboard(state);
}
