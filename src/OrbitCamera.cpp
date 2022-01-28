#include "OrbitCamera.hpp"
#include "Actor.hpp"
OrbitCamera::OrbitCamera(class Actor* owner)
	:CameraComponent(owner)
	,mOffset(-400,0,0)
	,mUp(0,0,1)
	,mPitchSpeed(0)
	,mYawSpeed(0)
{
}

void OrbitCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	const Quaternion yaw(mUp, mYawSpeed*deltaTime);
	mOffset = Vector3::Transform(mOffset, yaw);
	mUp = Vector3::Transform(mUp, yaw);

	Vector3 forward = -1.0* mOffset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(mUp, forward);
	right.Normalize();

	const Quaternion pitch(right, mPitchSpeed*deltaTime);
	mOffset = Vector3::Transform(mOffset, pitch);
	mUp = Vector3::Transform(mUp, pitch);

	const Vector3 target = mOwner->GetPosition();
	const Vector3 cameraPos = target + mOffset;
	const Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
	SetViewMatrix(view);
}
