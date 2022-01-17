#pragma once
#include "Actor.hpp"

class CameraActor :
	public Actor
{
	CameraActor(class Game* game):Actor(game){}
	~CameraActor() override = default;
};

