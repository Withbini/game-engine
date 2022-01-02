#pragma once
class Actor;
class Component
{
public:
	explicit Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	Actor* mOwner;
	int mUpdateOrder;
	
	//TODO: implementation hash function
};