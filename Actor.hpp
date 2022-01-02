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

	//TODO :impl. rule of five

	void Update(float deltaTime);
	virtual void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	//getter setter
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	float getScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	class Game* GetGame() const { return mGame; }
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	class Game* mGame;
};
