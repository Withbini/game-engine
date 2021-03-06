#include <SDL_mouse.h>
#include <SDL_scancode.h>

#include "FollowActor.hpp"
#include "FollowCamera.hpp"
#include "MirrorCamera.hpp"
#include "MoveComponent.hpp"

FollowActor::FollowActor(Game* game)
	:Actor(game)
	,mCamera(nullptr)
	,mMove(nullptr)
	,mMirror(nullptr)
{
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	mCamera = new FollowCamera(this);
	mMove = new MoveComponent(this);
	mMirror = new MirrorCamera(this);
}

void FollowActor::ActorInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::Pi;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		angularSpeed += Math::Pi;
	}

	mMove->SetForwardSpeed(forwardSpeed);
	mMove->SetAngularSpeed(angularSpeed);

	if(!Math::NearZero(forwardSpeed))
	{
		mCamera->SetHorzDist(500.f);
	}
	else
	{
		mCamera->SetHorzDist(350.f);
	}
}