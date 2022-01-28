#pragma once
#include "CameraComponent.hpp"

class FollowCamera :
	public CameraComponent
{
public:
	FollowCamera(class Actor* owner);
	~FollowCamera() override = default;

	void Update(float deltaTime) override;

	float GetHorzDist() const { return mHorzDist; }	void SetHorzDist(const float horz_dist) { mHorzDist = horz_dist; }	float GetVertDist() const { return mVertDist; }	void SetVertDist(const float vert_dist) { mVertDist = vert_dist; }	float GetTargetDist() const { return mTargetDist; }	void SetTargetDist(const float target_dist) { mTargetDist = target_dist; }	float GetSpringConstant() const { return mSpringConstant; }	void SetSpringConstant(const float spring_constant) { mSpringConstant = spring_constant; }

private:
	float mHorzDist;
	float mVertDist;
	float mTargetDist;

	float mSpringConstant;
	Vector3 GetCameraPos() const;
};

