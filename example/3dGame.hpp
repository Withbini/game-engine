#pragma once
#include "Game.hpp"

class GL3DGame
	:public Game{
public:
	GL3DGame() = default;
	~GL3DGame() override = default;

	void LoadData() override;
	void ChangeCamera(uint8_t keyState) override;
private:
	class FPSActor* mCameraActor;
	class SplineActor* mSplineActor;
};