#pragma once
#include <vector>


#include "Math.hpp"
#include "SpriteComponent.hpp"
class Actor;

class BGSpriteComponent:public SpriteComponent
{
public:
	BGSpriteComponent(Actor* owner, int drawOrder = 10);
	void Update(float deltaTime) override;
	//void Draw(SDL_Renderer* renderer) override;
	void Draw(Shader* renderer) override;

	void SetBGTextures(const std::vector<Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	struct BGTexture
	{
		Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};
