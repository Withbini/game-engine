#pragma once
#include "Component.hpp"
#include "Model.hpp"

class MeshComponent :
	public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent() override;

	virtual void Draw(class Shader* shader);
	void BindTextures(class Shader* shader) const;
	void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	void SetModel(ModelUPtr mesh) { mModel = std::move(mesh); }
	void SetTextureIndex(size_t idx) { mTextureIdx = idx; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }
private:
	class Mesh* mMesh;
	ModelUPtr mModel;
	size_t mTextureIdx;
	bool mVisible;
};

