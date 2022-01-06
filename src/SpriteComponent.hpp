#pragma once
#include <SDL.h>
#include "Component.hpp"

class SpriteComponent : public Component
{
public:
	explicit SpriteComponent(class Actor* owner,int drawOrder = 100);
	virtual ~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTextureHeight; }
	int GetTexWidth() const { return mTextureWidth; }
private:
	SDL_Texture* mTexture;
	
	int mDrawOrder;
	int mTextureWidth;
	int mTextureHeight;
};

