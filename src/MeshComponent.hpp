#pragma once
#include "Component.hpp"

class MeshComponent :
	public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent() override;

	virtual void Draw(class Shader* shader);
	void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	void SetTextureIndex(size_t idx) { mTextureIdx = idx; }
private:
	class Mesh* mMesh;
	size_t mTextureIdx;
};

