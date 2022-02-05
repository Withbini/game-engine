#pragma once
#include "Actor.hpp"

class FPSModel :
	public Actor
{
public:
	FPSModel(class Game* game);
	~FPSModel() override = default;
};

