#include "Ship2.hpp"
#include "AnimSpriteComponent.hpp"
#include "AsteroidGame.hpp"
#include "CircleComponent.hpp"
#include "InputComponent.hpp"
#include "Laser.hpp"

Ship2::Ship2(Game* game)
	:Actor(game)
	, mCoolDown(0.f)
{
	auto* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Ship.png"));

	auto *input = new InputComponent(this);
	input->SetForwardKey(SDL_SCANCODE_W);
	input->SetBackKey(SDL_SCANCODE_S);
	input->SetClockwiseKey(SDL_SCANCODE_A);
	input->SetCounterClockwiseKey(SDL_SCANCODE_D);
	input->SetMaxForwardSpeed(300.f);
	input->SetMaxAngularSpeed(Math::TwoPi);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.f);
}

void Ship2::UpdateActor(float deltaTime)
{
	mCoolDown -= deltaTime;
}

void Ship2::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mCoolDown <= 0.0f)
	{
		auto*laser = new Laser(this->GetGame());
		laser->SetPosition(this->GetPosition());
		laser->SetRotation(this->GetRotation());
		//initialize
		mCoolDown = 0.5f;
	}
}
