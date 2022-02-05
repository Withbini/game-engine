#pragma once
#include "Actor.hpp"

class OrbitActor :
	public Actor
{
public:
	OrbitActor(class Game* game);
	~OrbitActor() override = default;
	void ActorInput(const uint8_t* keyState) override;
private:
	class OrbitCamera* mCamera;
	class MoveComponent* mMove;
};

