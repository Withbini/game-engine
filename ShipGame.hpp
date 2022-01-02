#pragma once
#include "Game.hpp"

class ShipGame:public Game
{
public:
	ShipGame():Game(),mShip(nullptr){}
	~ShipGame() = default;
	void LoadData() override;
private:
	class Ship* mShip;
};

