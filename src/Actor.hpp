#pragma once
#include <unordered_set>
#include "Component.hpp"
#include "Math.hpp"
class Actor
{
public:
	enum State
	{
		EActive = 0,
		EPause,
		EDead
	};

	explicit Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	virtual void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState){}

	//getter setter
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }

	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	class Game* GetGame() const { return mGame; }
	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	class Game* mGame;

	//TODO:manage component deletion
};
