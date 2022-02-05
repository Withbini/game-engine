#include <SDL_mouse.h>
#include <SDL_scancode.h>

#include "OrbitCamera.hpp"
#include "OrbitActor.hpp"
#include "MoveComponent.hpp"

OrbitActor::OrbitActor(Game* game)
	:Actor(game)
	, mCamera(nullptr)
	, mMove(nullptr)
{
	mCamera = new OrbitCamera(this);
	mMove = new MoveComponent(this);
}

void OrbitActor::ActorInput(const uint8_t* keyState)
{
	int x, y;
	auto button = SDL_GetRelativeMouseState(&x, &y);
	if (button & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		const int maxMouseSpeed = 500;
		const float maxAngularSpeed = Math::Pi * 8;
		float angularSpeed = 0.f;
		if (x != 0)
		{
			angularSpeed = static_cast<float>(x) / maxMouseSpeed;
			angularSpeed *= maxAngularSpeed;
		}
		mCamera->SetYawSpeed(angularSpeed);

		const float maxPitchSpeed = Math::Pi * 8;
		float pitchSpeed = 0.f;
		if (y != 0)
		{
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxPitchSpeed;
		}
		mCamera->SetPitchSpeed(pitchSpeed);
	}
}