#include "FollowCamera.hpp"
#include "CameraComponent.hpp"
#include "Actor.hpp"

FollowCamera::FollowCamera(Actor* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(500.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(64.0f)
{
}

void FollowCamera::Update(float deltaTime)
{
	Matrix4 view;
	Vector3 cameraPos = GetCameraPos();
	Vector3 target = mOwner->GetPosition() + mOwner->GetForward()* mTargetDist;
	view = Matrix4::CreateLookAt(cameraPos, target, Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::GetCameraPos() const
{
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward()*mHorzDist;
	cameraPos += Vector3::UnitZ*mVertDist;
	return cameraPos;
}
