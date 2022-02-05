#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Math.hpp"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner, drawOrder)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTextureWidth(0)
	,mTextureHeight(0)
	,mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTextureWidth),static_cast<float>(mTextureHeight),1.0f);
		Matrix4 worldMat = scaleMat * mOwner->GetWorldTransform();
		shader->setMat4("world", worldMat);
		mTexture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(TexturePtr texture)
{
	mTexture = texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}