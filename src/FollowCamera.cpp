#include "FollowCamera.hpp"
#include "CameraComponent.hpp"
#include "Actor.hpp"

FollowCamera::FollowCamera(Actor* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(250.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(128.0f)
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	float dampening = 2.f * Math::Sqrt(mSpringConstant);

	Vector3 idealPos = GetCameraPos();
	Vector3 diff = mActualPos - idealPos;
	Vector3 accel = -mSpringConstant * diff - dampening * mVelocity;

	mVelocity += accel * deltaTime;
	mActualPos += mVelocity * deltaTime;

	Vector3 target = mOwner->GetPosition() + mOwner->GetForward()* mTargetDist;
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::GetCameraPos() const
{
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward()*mHorzDist;
	cameraPos += Vector3::UnitZ*mVertDist;
	return cameraPos;
}
