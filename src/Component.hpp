#pragma once
#include <cstdint>
class Actor;
class Component
{
public:
	explicit Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

	virtual void ProcessInput(const uint8_t* keyState){}
	virtual void onUpdateWorldTransform(){}
protected:
	Actor* mOwner;
	int mUpdateOrder;
	
	//TODO: implementation hash function
};