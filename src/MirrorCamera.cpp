#include "MirrorCamera.hpp"

#include "Actor.hpp"
#include "Game.hpp"

MirrorCamera::MirrorCamera(Actor* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(250.0f)
	, mTargetDist(100.0f)
{
}

MirrorCamera::~MirrorCamera()
{
}

void MirrorCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Vector3 idealPos = ComputeCameraPos();
	Vector3 target = mOwner->GetPosition() -
		mOwner->GetForward() * mTargetDist;
	Matrix4 view = Matrix4::CreateLookAt(idealPos, target,
		Vector3::UnitZ);
	mOwner->GetGame()->GetRenderer()->mMirrorView = view;
}

Vector3 MirrorCamera::ComputeCameraPos() const
{
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos += mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}