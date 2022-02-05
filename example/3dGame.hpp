#pragma once
#include "Game.hpp"

class GL3DGame
	:public Game{
public:
	GL3DGame() = default;
	~GL3DGame() override = default;

	void LoadData() override;
	void HandleKeyPress(SDL_KeyboardEvent* key) override;
	
private:
	void ChangeCamera(int key);

	class FPSActor* mFPSActor;
	class SplineActor* mSplineActor;
	class FollowActor* mFollowActor;
	class OrbitActor* mOrbitActor;
};