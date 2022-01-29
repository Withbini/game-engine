#include "FollowActor.hpp"
#include "FollowCamera.hpp"
#include "MoveComponent.hpp"

FollowActor::FollowActor(Game* game)
	:Actor(game)
	,mCamera(nullptr)
	,mMove(nullptr)
{
	mCamera = new FollowCamera(this);
	mMove = new MoveComponent(this);
}

void FollowActor::ActorInput(const uint8_t* keyState)
{
	
}

void FollowActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}
