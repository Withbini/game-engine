#pragma once
#include "Actor.hpp"

class Ship2 :public Actor
{
public:
	Ship2(class AsteroidGame* game);

	void UpdateActor(float deltaTime) override;

	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
};