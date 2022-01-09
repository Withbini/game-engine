#pragma once
#include "Actor.hpp"

class Laser :
	public Actor
{
public:
	Laser(class Game* game);
	~Laser() override;
	void UpdateActor(float deltaTime) override;
private:
	class CircleComponent* mCircle;
	float mDeathTimer;
};

