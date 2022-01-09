#define _CRT_SECURE_NO_WARNINGS
#include "Game.hpp"
#include "SDL_image.h"
#include "SpriteComponent.hpp"

Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	const int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("example", 100, 100, WINDOW_WIDGHT, WINDOW_HEIGHT, 0);
	if (mWindow == nullptr)
	{
		SDL_Log("Unable to create SDL Window : %s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mWindow == nullptr)
	{
		SDL_Log("Unable to create SDL Window : %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	LoadData();
	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		default:
			break;
		}
	}

	const uint8_t* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;

	mUpdatingActors = true;
	for(auto actor:mActors)
		actor->ProcessInput(state);
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)){}

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	mUpdatingActors = true;
	for (auto *actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto *pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*>deadActors;
	for (auto *actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto &actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for(auto* sprite: mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
}

void Game::UnloadData()
{
	while(!mActors.empty())
	{
		delete mActors.back();
	}

	for(auto texture: mTextures)
	{
		SDL_DestroyTexture(texture.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::LoadTexture(const std::string& fileName) const
{
	auto *fp= fopen(fileName.c_str(),"r");
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (!surface)
	{
		SDL_Log("%s", SDL_GetError());
		SDL_Log("Failed to load texture file %s", fileName.c_str());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
		return nullptr;
	}
	return texture;
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	auto textureFromFile = mTextures.find(fileName);
	if (textureFromFile == mTextures.end()){
		auto* texture = LoadTexture(fileName);
		mTextures.insert({ fileName, texture });
		return texture;
	}
	return textureFromFile->second;
}

void Game::AddSprite(SpriteComponent* sprite)
{
	const int drawOrder = sprite->GetDrawOrder();
	auto it = mSprites.begin();
	for (; it != mSprites.end(); ++it)
	{
		if (drawOrder < (*it)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(it, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto delSprite = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(delSprite);
}