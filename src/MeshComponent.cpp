#include "MeshComponent.hpp"

#include "Actor.hpp"
#include "Format.hpp"
#include "Game.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
	, mMesh(nullptr)
	, mTextureIdx(0)
	, mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		shader->setMat4("world", mOwner->GetWorldTransform());
		shader->setFloat("specPower", mMesh->GetSpecPower());

		if (mMesh->mTextures.size() > 1)
		{
			for (int i = 0; i < mMesh->mTextures.size(); ++i)
			{
				auto t = mMesh->GetTexture(i);
				if (t) t->Bind(i);
				auto st= Format::string_format("uTexture%d", i);
				shader->setInt(st, i);
			}
			glActiveTexture(GL_TEXTURE0);
		}
		else {
			auto t = mMesh->GetTexture(mTextureIdx);
			if (t) t->Bind();
		}
		VertexArray* va = mMesh->GetVertexArray();
		va->Bind();
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
