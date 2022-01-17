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
		const auto rotation = mOwner->GetRotation();
		const float angle = mAngularSpeed * deltaTime;
		auto newRot = Quaternion(Vector3::UnitZ, angle);
		Quaternion::Concatenate(rotation, newRot);
		mOwner->SetRotation(newRot);
	}
	
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		if (pos.x <= -640.0f) { pos.x = -640.f; }
		else if (pos.x >= 640.0f) { pos.x = 640.0f; }

		if (pos.y <= -360.0f) { pos.y = -360.0f; }
		else if (pos.y >= 360.0f) { pos.y = 360.0f; }

		mOwner->SetPosition(pos);
	}
}
