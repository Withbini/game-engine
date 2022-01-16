#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture() = default;

	bool Load(const std::string& file);
	void UnLoad();
	void SetActive() const;
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};

