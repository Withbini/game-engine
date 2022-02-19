#include <SDL_log.h>
#include <glad/glad.h>

#include "Texture.hpp"
#include "Image.hpp"

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{}

Texture::~Texture()
{
	if (mTextureID)
		glDeleteTextures(1, &mTextureID);
}

TexturePtr Texture::CreateFromImage(const class Image* image) //TODO: change to unique pointer
{
	auto texture = TexturePtr(new Texture);
	texture->CreateTexture();
	texture->SetTextureFromImage(image);

	return texture;
}

TexturePtr Texture::Create(int width, int height, uint32_t format, uint32_t type)
{
	auto texture = TexturePtr(new Texture);
	texture->CreateTexture();
	texture->SetTextureFormat(width, height, format, type);
	texture->SetFilter(GL_NEAREST, GL_NEAREST);

	return texture;
}

void Texture::CreateTexture()
{
	glGenTextures(1, &mTextureID);
	Bind();
	SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	//SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}

void Texture::Bind(int index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	debug("active");
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	debug("bind texture");
}

void Texture::SetTextureFromImage(const Image* image) {
	GLenum format = GL_RGBA;
	switch (image->GetChannel()) {
	case 1: format = GL_RED; debug("channel 1"); break;
		case 2: format = GL_RG; debug("channel 2"); break;
		case 3: format = GL_RGB; debug("channel 3"); break;
		default: break;
	}
	mWidth = image->GetWidth();
	mHeight = image->GetHeight();
	mFormat = format;
	mType = GL_UNSIGNED_BYTE;
	glTexImage2D(GL_TEXTURE_2D, 0, mFormat, image->GetWidth(), image->GetHeight(), 0, format, mType, image->GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	if(GLAD_GL_EXT_texture_filter_anisotropic)
	{
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &largest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}
}

void Texture::SetTextureFormat(int width, int height, uint32_t format, uint32_t type)
{
	mWidth = width;
	mHeight = height;
	mFormat = format;
	mType = type;

	GLenum imageFormat = GL_RGBA;
	if (mFormat == GL_DEPTH_COMPONENT)
	{
		imageFormat = GL_DEPTH_COMPONENT;
	}
	else if (mFormat == GL_RGB ||
		mFormat == GL_RGB16F ||
		mFormat == GL_RGB32F)
	{
		imageFormat = GL_RGB;
	}
	else if (mFormat == GL_RED ||
		mFormat == GL_R16F ||
		mFormat == GL_R32F)
	{
		imageFormat = GL_RED;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, imageFormat, type, nullptr);
}
