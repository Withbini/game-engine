#include "Ship2.hpp"
#include <SDL_render.h>
#include "AnimSpriteComponent.hpp"
#include "AsteroidGame.hpp"
#include "InputComponent.hpp"

Ship2::Ship2(AsteroidGame* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	auto asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship.png"),
		game->GetTexture("Assets/ShipWithThrust.png"),
	};
	asc->SetAnimTextures(anims);

	//inputcomponent Ãß°¡
	auto* input = new InputComponent(this);
}

void Ship2::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 1255.f)
	{
		pos.x = 1255.f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 720.0f)
	{
		pos.y = 720.0f;
	}
	SetPosition(pos);
}

void Ship2::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}
