#include "Actor.hpp"
#include "Game.hpp"
#include <algorithm>

Actor::Actor(Game* game)
	: mState(EActive)
	, mPosition(0, 0)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if(mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* comp)
{
	const auto it = find(mComponents.begin(), mComponents.end(), comp);
	if (it == mComponents.end())
	{
		mComponents.emplace_back(comp);
	}
}

void Actor::RemoveComponent(Component* comp)
{
	const auto it = find(mComponents.begin(), mComponents.end(), comp);
	if (it != mComponents.end())
	{
		mComponents.erase(it);
	}
}
