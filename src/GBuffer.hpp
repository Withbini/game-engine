#pragma once
#include <vector>
#include "Texture.hpp"

class GBuffer
{
public:
	enum
	{
		EDiffuse=0,
		ENormal,
		EWorldPos,
		NUM_GBUFFER_TEXTURES
	};
	GBuffer() = default;
	~GBuffer() = default;
	
	bool Create(int width,int height);
	void Destroy();

	TexturePtr GetTexture(int index);
	unsigned int GetBufferID() const { return mBufferID; }
	void SetTexturesActive();
private:
	unsigned int mBufferID {0};
	std::vector<TexturePtr> mTextures;
};