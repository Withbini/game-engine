#include "BGSpriteComponent.hpp"
#include "Actor.hpp"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto &bg : mBGTextures)
	{
		bg.mOffset.x += mScrollSpeed * deltaTime;
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1.f)  * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(Shader* shader)
{
}

void BGSpriteComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
	auto  count = 0;
	for (const auto&tex : textures)
	{
		BGTexture tmp;
		tmp.mTexture = tex;
		tmp.mOffset.x = count * mScreenSize.x;
		tmp.mOffset.y = 0;
		mBGTextures.emplace_back(tmp);
		count++;
	}
}
