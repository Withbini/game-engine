#include "CameraActor.hpp"
#include <SDL.h>

#include "Game.hpp"
#include "MoveComponent.hpp"
CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//카메라 위치, target 위치 설정
	Vector3 cameraPos = GetPosition();
	Vector3 eye = cameraPos + GetForward() * 100.f;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, eye, Vector3::UnitZ);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const uint8_t* keyState)
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
}
