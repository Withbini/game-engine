#include "AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mCurrFrame(0.0f),
	mAnimFPS(24.0f)
{
	mCurrFrame = 0;
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (!mAnimTextures.empty())
	{
		mCurrFrame += mAnimFPS * deltaTime;
		while (static_cast<size_t>(mCurrFrame) >= mAnimTextures.size())
		{
			mCurrFrame -= static_cast<float>(mAnimTextures.size());
		}

		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

//void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
//{
//	mAnimTextures = textures;
//	if (!mAnimTextures.empty())
//	{
//		mCurrFrame = 0.f;
//		SetTexture(mAnimTextures[0]);
//	}
//}

void AnimSpriteComponent::SetAnimTextures(const std::vector<Texture*>& textures)
{
	mAnimTextures = textures;
	if (!mAnimTextures.empty())
	{
		mCurrFrame = 0.f;
		SetTexture(mAnimTextures[0]);
	}
}
