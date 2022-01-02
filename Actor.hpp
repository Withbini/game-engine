#pragma once
#include <unordered_set>
#include "Component.hpp"
#include "Vector.hpp"

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

	//getter
	const Vector2& getPosition() const { return mPosition; }
	State GetState() const { return mState; }
	float getScale() const { return mScale; }
	float getRotation() const { return mRotation; }

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	class Game* mGame;
};
