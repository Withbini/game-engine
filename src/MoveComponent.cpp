#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rotation = mOwner->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
	}
	
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		if (pos.x <= -640.0f) { pos.x = -640.f; }
		else if (pos.x >= 640.0f) { pos.x = 640.0f; }

		if (pos.y <= -360.0f) { pos.y = -360.0f; }
		else if (pos.y >= 360.0f) { pos.y = 360.0f; }

		mOwner->SetPosition(pos);
	}
}
