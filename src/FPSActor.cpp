#include "FPSActor.hpp"

#include "Game.hpp"
#include "MoveComponent.hpp"
#include "FPSCamera.hpp"
#include "FPSModel.hpp"
#include "FollowCamera.hpp"

FPSActor::FPSActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mCamera = new FPSCamera(this);
	mCamera->SetVisible(true);
	mFollowCamera = new FollowCamera(this);

	mFPSModel = new FPSModel(this->GetGame());
	mFPSModel->Load("Assets/rifle.gpmesh");
	mFPSModel->SetVisible(true);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//if (mFPSModel->GetVisible()) {
		const Vector3 modelPosOffset(10.f, 25.f, -10.f);
		Vector3 modelPos = GetPosition();
		modelPos += GetForward() * modelPosOffset.x;
		modelPos += GetRight() * modelPosOffset.y;
		modelPos.z += modelPosOffset.z;
		mFPSModel->SetPosition(modelPos);

		Quaternion q = GetRotation();
		q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCamera->GetPitch()));
		mFPSModel->SetRotation(q);
	//}
}

void FPSActor::ActorInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

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
		strafeSpeed -= 400.0f;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}
	if(keyState[SDL_SCANCODE_1])
	{
		mCamera->SetVisible(true);
		mFPSModel->SetVisible(true);
		mFollowCamera->SetVisible(false);
	}
	else if (keyState[SDL_SCANCODE_2])
	{
		mCamera->SetVisible(false);
		mFPSModel->SetVisible(false);
		mFollowCamera->SetVisible(true);
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
