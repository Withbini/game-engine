#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner)
	,mRadius(0.0f)
{
	
}

const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	const Vector2 diff = a.GetCenter() - b.GetCenter();
	const float distSq = diff.LengthSq();

	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
