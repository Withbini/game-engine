#pragma once
#include "Game.hpp"

class ShipGame:public Game
{
public:
	ShipGame():Game(),mShip(nullptr){}
	~ShipGame() override= default;
	void LoadData() override;

	void ProcessInput() override;
private:
	class Ship* mShip;
};

