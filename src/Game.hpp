#pragma once
#include <vector>
#include <unordered_map>

#include "Actor.hpp"
#include "Asteroid.hpp"
#include "Renderer.hpp"

class Game
{
public:
	Game();
	virtual ~Game();
	virtual bool Initialize()=0;
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	//for chapter3
	void AddAsteroid(class Asteroid* asteroid)
	{
		mAsteroid.push_back(asteroid);
	}
	std::vector<Asteroid*> GetAsteroid() const { return mAsteroid; }
	void SetAsteroid(const std::vector<Asteroid*>& m_asteroid) { mAsteroid = m_asteroid; }
	void RemoveAsteroid(Asteroid* asteroid)
	{
		auto iter = std::find(mAsteroid.begin(),mAsteroid.end(), asteroid);
		if (iter != mAsteroid.end())
			mAsteroid.erase(iter);
	}

	Renderer* GetRenderer() const {return mRenderer;}
private:
	std::vector<class Asteroid*>mAsteroid;
	

	void UnloadData();
	void UpdateGame();
protected:
	virtual void ProcessInput();
	virtual void LoadData();
	void GenerateOutput() const;

	bool mIsRunning;
	Uint32 mTicksCount;
	const int WINDOW_HEIGHT = 720;
	const int WINDOW_WIDTH = 1280;

	//actor
	std::vector<Actor*>mActors;
	std::vector<Actor*>mPendingActors;
	bool mUpdatingActors;

	Renderer* mRenderer;
};