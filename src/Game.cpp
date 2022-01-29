#include "Game.hpp"
#include "SDL_image.h"
#include "SpriteComponent.hpp"
#include "Renderer.hpp"

Game::Game()
	: mIsRunning(true)
	, mUpdatingActors(false)
	, mRenderer(nullptr)
{
}

Game::~Game()
{
	if(mRenderer)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

bool Game::Initialize()
{
	mRenderer = new	Renderer(this);
	if (!mRenderer->Initialize((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}
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
	if(mRenderer)
	{
		mRenderer->Shutdown();
	}
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
	for (auto* actor : mActors)
		actor->ProcessInput(state);
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {}

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
		pending->ComputeWorldTransform();
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

	for (auto* actor : deadActors)
	{
		delete actor;
	}
}

void Game::ChangeCamera(uint8_t keyState)
{
}
void Game::GenerateOutput() const
{
	mRenderer->Draw();
}

void Game::LoadData()
{
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	if(mRenderer)
		mRenderer->UnloadData();
}