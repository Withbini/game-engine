#pragma once
#include "Game.hpp"

class ShipGame:public Game
{
public:
	ShipGame():Game(),mShip(nullptr){}
	~ShipGame() override= default;
	void LoadData() override;

	//TODO:input process by inputComponent class
	void ProcessInput();
private:
	class Ship* mShip;
};

