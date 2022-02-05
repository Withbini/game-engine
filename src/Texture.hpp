#pragma once
#include "Common.hpp"

CLASS_PTR(Texture)
class Texture
{
public:
	~Texture();

	static TexturePtr CreateFromImage(const class Image* image);
	static TexturePtr Create(int width,int height, uint32_t format, uint32_t type = GL_UNSIGNED_BYTE);
	void SetFilter(uint32_t min, uint32_t mag) const;
	void SetWrap(uint32_t sWrap, uint32_t tWrap) const;
	void Bind(int index=0) const;
	
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	uint32_t GetFormat() const { return mFormat; }
	uint32_t GetType() const { return mType; }
	const uint32_t GetTextureID() const { return mTextureID; }
private:
	Texture();
	void CreateTexture();
	void SetTextureFromImage(const Image* image);
	void SetTextureFormat(int width, int height, uint32_t format, uint32_t type);

	unsigned int mTextureID;
	int mWidth;
	int mHeight;
	uint32_t mFormat;
	uint32_t mType;
};

