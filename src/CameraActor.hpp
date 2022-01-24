#pragma once
#include "Actor.hpp"

class CameraActor :
	public Actor
{
public:
	CameraActor(class Game* game);
	~CameraActor() override = default;
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	class MoveComponent* mMoveComp;
};

