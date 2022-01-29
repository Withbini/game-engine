#include "SplineCamera.hpp"
#include "Actor.hpp"


SplineCamera::SplineCamera(class Actor* owner)
	:CameraComponent(owner)
	, mT(0)
	, mPause(false)
	, mSpeed(0.5f)
	, mPath(nullptr)
{

}

void SplineCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	if (!mPause)
	{
		mT += mSpeed * deltaTime;
		if (mT >= 1.f)
		{
			if (mIndex < mPath->getNumControlPoints() - 3)
			{
				mIndex++;
				mT -= 1.0f;
			}
			else
			{
				mPause = true;
			}
		}
	}
	Vector3 cameraPos = mPath->Compute(mIndex, mT);
	Vector3 target = mPath->Compute(mIndex, mT + 0.01f);
	const Vector3 up = Vector3::UnitZ;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}