#include "GBuffer.hpp"
#include <cassert>

bool GBuffer::Create(int width, int height)
{
	glGenFramebuffers(1, &mBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, mBufferID);

	for (int i = 0; i < NUM_GBUFFER_TEXTURES; ++i)
	{
		auto texture = Texture::Create(width, height, GL_RGB32F, GL_FLOAT);
		mTextures.emplace_back(texture);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, texture->GetTextureID(), 0);
	}

	std::vector<GLenum> attachments(NUM_GBUFFER_TEXTURES);
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; ++i)
	{
		attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	}
	glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());

	GLuint depthbuffer;
	glGenRenderbuffers(1, &depthbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Destroy();
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void GBuffer::Destroy()
{
	if (mBufferID != 0)
		glDeleteFramebuffers(1, &mBufferID);
	while (!mTextures.empty())
		mTextures.pop_back();
}

TexturePtr GBuffer::GetTexture(int index)
{
	assert((unsigned long long) index < this->mTextures.size());
	return mTextures[index];
}

void GBuffer::SetTexturesActive()
{
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		mTextures[i]->Bind(i);
	}
}