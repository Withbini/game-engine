#pragma once
#include "Actor.hpp"
#include "CircleComponent.hpp"

class Ship2 :public Actor
{
public:
	Ship2(class Game* game);
	~Ship2() override=default;

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	float mCoolDown;
	CircleComponent* mCircle;
};
