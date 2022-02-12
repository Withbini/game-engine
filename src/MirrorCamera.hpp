#pragma once
#include "CameraComponent.hpp"

class MirrorCamera :
	public CameraComponent
{
public:
	MirrorCamera(class Actor* owner);
	~MirrorCamera() override;
	void Update(float deltaTime) override;

	float GetHorzDist() const { return mHorzDist; }	void SetHorzDist(const float horz_dist) { mHorzDist = horz_dist; }	float GetVertDist() const { return mVertDist; }	void SetVertDist(const float vert_dist) { mVertDist = vert_dist; }	float GetTargetDist() const { return mTargetDist; }	void SetTargetDist(const float target_dist) { mTargetDist = target_dist; }
private:
	Vector3 ComputeCameraPos() const;
	float mHorzDist;
	float mVertDist;
	float mTargetDist;
};

