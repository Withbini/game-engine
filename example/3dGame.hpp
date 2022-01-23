#pragma once
#include "Game.hpp"

class GL3DGame
	:public Game{
public:
	GL3DGame();
	~GL3DGame() override;

	void LoadData() override;
private:
};