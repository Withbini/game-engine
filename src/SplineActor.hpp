#pragma once
#include "Actor.hpp"

class SplineActor :
	public Actor
{
public:
	SplineActor(class Game*game);
	~SplineActor() override = default;
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;
private:
	class MoveComponent* mMoveComp;
	class SplineCamera* mCamera;
};

