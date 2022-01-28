#include "FPSCamera.hpp"
#include "Actor.hpp"

FPSCamera::FPSCamera(class Actor* owner)
	:CameraComponent(owner)
	, mPitch(0)
	, mMaxPitch(Math::Pi /3.f)
	, mPitchSpeed(0.f)
{
}

void FPSCamera::Update(float deltaTime)
{
	Vector3 cameraPos = mOwner->GetPosition();
	CameraComponent::Update(deltaTime);
	mPitch += mPitchSpeed * deltaTime;
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	Quaternion q(mOwner->GetRight(), mPitch); //direction and angle
	Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), q);
	Vector3 target = cameraPos + viewForward * 100.f;
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}
