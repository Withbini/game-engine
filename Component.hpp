#pragma once
<<<<<<< HEAD
class Actor;
=======

>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
class Component
{
public:
	explicit Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
<<<<<<< HEAD
	Actor* mOwner;
=======
	class Actor* mOwner;
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
	int mUpdateOrder;
	
	//TODO: implementation hash function
};