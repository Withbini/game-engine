#include "ShipGame.hpp"
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
}

void ShipGame::ProcessInput()
{
	Game::ProcessInput();
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	mShip->ProcessKeyboard(state);
}
