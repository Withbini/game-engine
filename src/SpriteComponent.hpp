#pragma once
#include "Component.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class SpriteComponent : public Component
{
public:
	explicit SpriteComponent(class Actor* owner,int drawOrder = 100);
	~SpriteComponent() override;
	//virtual void Draw(SDL_Renderer* renderer);
	virtual void Draw(Shader* shader);
	virtual void SetTexture(Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTextureHeight; }
	int GetTexWidth() const { return mTextureWidth; }
private:
	Texture* mTexture;
	
	int mDrawOrder;
	int mTextureWidth;
	int mTextureHeight;
};

