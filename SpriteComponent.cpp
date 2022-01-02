#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Math.hpp"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner, drawOrder)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
<<<<<<< HEAD
		r.w = static_cast<int>(mTextureWidth) * static_cast<int>(mOwner->getScale());
		r.h = static_cast<int>(mTextureHeight) * static_cast<int>(mOwner->getScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w/2.f);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2.f);
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
=======
		r.w = static_cast<int>(mTextureWidth) * mOwner->getScale();
		r.h = static_cast<int>(mTextureHeight) * mOwner->getScale();
		r.x = static_cast<int>(mOwner->getPosition().x - r.w/2.);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2.);
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->getRotation()), nullptr, SDL_FLIP_NONE);
>>>>>>> f3b02b0f031eb1b6202f2d404ef56fb3eff677c6
	}

}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
