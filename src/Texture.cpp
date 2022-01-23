#include "Texture.hpp"
#include <SDL_log.h>
#include <GL/glew.h>
#include "stb_image.h"

Texture::Texture():
	mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;

	unsigned char* image = stbi_load(fileName.c_str(),
		&mWidth, &mHeight, &channels, 0);
	if (image == nullptr)
	{
		SDL_Log("stbi failed to load image %s: ", fileName.c_str());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::UnLoad()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive() const
{
	//glActiveTexture(mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
