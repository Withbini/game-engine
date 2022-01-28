#pragma once
#include "CameraComponent.hpp"

class FollowCamera :
	public CameraComponent
{
public:
	FollowCamera(class Actor* owner);
	~FollowCamera() override = default;

	void Update(float deltaTime) override;

	float GetHorzDist() const { return mHorzDist; }

private:
	float mHorzDist;
	float mVertDist;
	float mTargetDist;

	float mSpringConstant;
	Vector3 GetCameraPos() const;
};
