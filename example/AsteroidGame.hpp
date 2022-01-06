#pragma once
#include "Game.hpp"

class AsteroidGame :
	public Game
{
public:
	AsteroidGame() = default;
	~AsteroidGame() override = default;
	void LoadData() override;
	void ProcessInput() override;
private:
	class Ship2* mShip;
};

