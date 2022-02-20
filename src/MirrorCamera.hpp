#pragma once
#include "CameraComponent.hpp"

class MirrorCamera :
	public CameraComponent
{
public:
	MirrorCamera(class Actor* owner);
	~MirrorCamera() override;
	void Update(float deltaTime) override;

	float GetHorzDist() const { return mHorzDist; }
private:
	Vector3 ComputeCameraPos() const;
	float mHorzDist;
	float mVertDist;
	float mTargetDist;
};
