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
	virtual void ActorInput(const uint8_t* keyState) {}

	//getter setter
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; mRecomputeWorldTransform = true; }

	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }

	Quaternion GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

	Vector3 GetForward() const { //시선방향으로 가기
		return Vector3::Transform(Vector3::UnitX, mRotation);
		}

	class Game* GetGame() const { return mGame; }
	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	void ComputeWorldTransform();
	Matrix4 GetWorldTransform() const { return mWorldTransform; }
private:
	State mState;
	Vector3 mPosition;
	float mScale;
	Quaternion mRotation; //회전축

	std::vector<Component*> mComponents;
	class Game* mGame;

	bool mRecomputeWorldTransform;
	Matrix4 mWorldTransform;
};
