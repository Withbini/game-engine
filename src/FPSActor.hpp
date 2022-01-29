#pragma once
#include "Actor.hpp"

class FPSActor :
	public Actor
{
public:
	FPSActor(class Game* game);
	~FPSActor() override = default;
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	class MoveComponent* mMoveComp;
	
	class FPSCamera* mCamera;
	class FPSModel* mFPSModel;
	class FollowCamera* mFollowCamera;
	class OrbitCamera* mOrbitCamera;
};

