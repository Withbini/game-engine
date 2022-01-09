#pragma once
#include "Actor.hpp"
class Asteroid : public Actor
{
public:
	Asteroid(class AsteroidGame* game);
	~Asteroid();
	
	class CircleComponent* GetCircle() const { return mCircle; }
private:
	class CircleComponent* mCircle;
};
