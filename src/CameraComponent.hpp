#pragma once
#include "Component.hpp"
#include "Math.hpp"

class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* owner,int order = 200);
	virtual ~CameraComponent();
protected:
	void SetViewMatrix(const Matrix4& view);
};
