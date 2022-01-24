#pragma once
#include "CameraComponent.hpp"

class FPSCamera: public CameraComponent
{
public:
	FPSCamera(class Actor* owner);
	~FPSCamera() override = default;
	void Update(float deltaTime) override;
	
	float GetPitch() const {return mPitch;}
	float GetMaxPitch() const { return mMaxPitch;}
	float GetPitchSpeed() const { return mPitchSpeed;}

	void SetMaxPitch(float max_pitch) {mMaxPitch = max_pitch;}
	void SetPitchSpeed(float pitch_speed) {mPitchSpeed = pitch_speed;}
private:
	float mPitch;
	float mMaxPitch;
	float mPitchSpeed;
};
