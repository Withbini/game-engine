#pragma once
#include "Math.hpp"
#include "MeshComponent.hpp"

class LightComponent :
	public Component
{
public:
	LightComponent(class Actor* owner);
	~LightComponent() override;
	void Draw(class Shader* shader, class Mesh*mesh) const;
	Vector3 mDiffuseColor;
	// Radius of light
	float mInnerRadius;
	float mOuterRadius;
};

