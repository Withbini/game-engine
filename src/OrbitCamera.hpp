#pragma once
#include "CameraComponent.hpp"

class OrbitCamera :public CameraComponent
{
public:
	OrbitCamera(class Actor* owner);
	~OrbitCamera() override = default;

	void Update(float deltaTime) override;

	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }
	void SetPitchSpeed(const float pitch_speed) { mPitchSpeed = pitch_speed; }
	void SetYawSpeed(const float yaw_speed) { mYawSpeed = yaw_speed; }
private:
	Vector3 mOffset;
	Vector3 mUp;
	float mPitchSpeed;
	float mYawSpeed;
};