#include "Component.hpp"
<<<<<<< HEAD
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner),
	mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
=======

Component::Component(Actor* owner, int updateOrder)
{
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
}

Component::~Component()
{
<<<<<<< HEAD
	mOwner->RemoveComponent(this);
=======
	
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
}

void Component::Update(float deltaTime)
{
}
