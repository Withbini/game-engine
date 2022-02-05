#include "SplineActor.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "SplineCamera.hpp"

SplineActor::SplineActor(Game* game)
	:Actor(game)
{
	mCamera = new SplineCamera(this);

	std::unique_ptr<Spline> path = std::make_unique<Spline>();
	path->mControlPoints.emplace_back(Vector3::Zero);
	for (int i = 0; i < 5; i++)
	{
		if (i % 2 == 0)
		{
			path->mControlPoints.emplace_back(Vector3(300.0f * (i + 1), 300.0f, 300.0f));
		}
		else
		{
			path->mControlPoints.emplace_back(Vector3(300.0f * (i + 1), 0.0f, 0.0f));
		}
	}
	mCamera->SetSpline(std::move(path));

	mMoveComp = new MoveComponent(this);
}

void SplineActor::ActorInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float angluarSpeed = 0.0f;

	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		angluarSpeed -= Math::PiOver2;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		angluarSpeed += Math::PiOver2;
	}

	mMoveComp->SetAngularSpeed(angluarSpeed);
	mMoveComp->SetForwardSpeed(forwardSpeed);
}

void SplineActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void SplineActor::ResetSpline() const
{
	mCamera->Reset();
}
