#pragma once
#include "Actor.hpp"

class FollowActor :
	public Actor
{
public:
	FollowActor(class Game*game);
	~FollowActor() override = default;
	void ActorInput(const uint8_t* keyState) override;
private:
	class FollowCamera* mCamera;
	class MoveComponent* mMove;
};

