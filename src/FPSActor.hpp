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

	void SetVisible(bool b);
private:
	class MoveComponent* mMove;
	class MeshComponent* mMesh;
	class FPSCamera* mCamera;
	class FPSModel* mFPSModel;
};

