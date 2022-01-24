#include "FPSActor.hpp"

#include "Game.hpp"
#include "MoveComponent.hpp"
#include "FPSCamera.hpp"

FPSActor::FPSActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mCamera = new FPSCamera(this);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void FPSActor::ActorInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		strafeSpeed -= 300.0f;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		strafeSpeed += 300.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.f;
	if (x != 0)
	{
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCamera->SetPitchSpeed(pitchSpeed);
}
