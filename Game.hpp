#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "Actor.hpp"
#include "Component.hpp"
#include "SDL.h"

class Game
{
public:
	Game()
	{
		mIsRunning = true;
		//mBallPos = { (float)WINDOW_WIDGHT / 2,(float)WINDOW_HEIGHT / 2 };
		//mPaddlePos = { static_cast<float>(thickness),static_cast<float>(WINDOW_HEIGHT / 2) };
		//mBallVel = Vector2{ -200.f,235.f };
	}
	~Game()
	{
		//really need this?
		/*for(auto *actor:mActors)
		{
			RemoveActor(actor);
		}*/
	}

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;

	const int thickness = 15;

	const int WINDOW_HEIGHT = 720;
	const int WINDOW_WIDGHT = 1280;

	uint32_t mTicksCount;

	//actor
	std::vector<Actor*>mActors;
	std::vector<Actor*>mPendingActors;
	bool mUpdatingActors;

	std::unordered_set<Component*> mComponents;
	
	void LoadData();
	void UnloadData();
	
	//TODO: wrapper
	//image
	SDL_Texture* LoadTexture(const std::string& fileName) const;
	//TODO:map container
	SDL_Texture* GetTexture(const std::string& fileName);
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	//std::map<std::string, SDL_Texture*> mTextures;

	//sprite?
	std::vector<class SpriteComponent*> mSprites;
};
