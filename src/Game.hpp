#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "Actor.hpp"
#include "Asteroid.hpp"
#include "Component.hpp"
#include "SDL.h"

class Game
{
public:
	Game();
	virtual ~Game() = default;
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	//for chapter3
	void AddAsteroid(Asteroid* asteroid)
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
private:
	std::vector<class Asteroid*>mAsteroid;
protected:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;

	const int WINDOW_HEIGHT = 720;
	const int WINDOW_WIDGHT = 1280;

	uint32_t mTicksCount;

	//actor
	std::vector<Actor*>mActors;
	std::vector<Actor*>mPendingActors;
	bool mUpdatingActors;

	std::unordered_set<Component*> mComponents;

	virtual void LoadData();
	virtual void UnloadData();

	//TODO: wrapper
	//image
	SDL_Texture* LoadTexture(const std::string& fileName) const;
	//TODO:map container
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//sprite
	std::vector<class SpriteComponent*> mSprites;
};
