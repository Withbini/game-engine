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
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mTextureWidth) * static_cast<int>(mOwner->GetScale());
		r.h = static_cast<int>(mTextureHeight) * static_cast<int>(mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w/2.f);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2.f);
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
