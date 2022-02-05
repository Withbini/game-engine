#include "MeshComponent.hpp"

#include "Actor.hpp"
#include "Game.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
	,mMesh(nullptr)
	,mTextureIdx(0)
	,mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if(mMesh)
	{
		shader->setMat4("world", mOwner->GetWorldTransform());
		shader->setFloat("specPower", mMesh->GetSpecPower());

		auto t = mMesh->GetTexture(mTextureIdx);
		if (t) t->Bind();
		VertexArray* va = mMesh->GetVertexArray();
		va->Bind();
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
