#include "Actor.hpp"
#include "Game.hpp"
#include <algorithm>

Actor::Actor(Game* game)
	: mState(EActive)
	, mPosition(0, 0)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
	, mRecomputeWorldTransform(true)
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
	if (mState == EActive)
	{
		ComputeWorldTransform(); //움직이기 전에

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform(); //움직인 후
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

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto* comp : mComponents)
			comp->ProcessInput(keyState);
		ActorInput(keyState);
	}
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

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

		for(auto *comp:mComponents)
		{
			comp->onUpdateWorldTransform();
		}
	}
}
