#pragma once
#include "Component.hpp"
#include "Math.hpp"

class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* owner,int order = 200);
	virtual ~CameraComponent();
	void SetVisible(bool visible);
protected:
	void SetViewMatrix(const Matrix4& view);
	bool mVisible;
};
