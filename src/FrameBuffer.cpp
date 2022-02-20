#include "FrameBuffer.hpp"

FrameBufferUPtr FrameBuffer::Create(int width, int height, uint32_t format, uint32_t type)
{
	auto buffer = FrameBufferUPtr(new FrameBuffer);
	if(buffer->Init(width, height, format, type))
		return std::move(buffer);
	return nullptr;
}

bool FrameBuffer::Init(int width, int height, uint32_t format, uint32_t type)
{
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	texture = Texture::Create(width, height, format, type);
	if(format ==GL_DEPTH_COMPONENT)
	{
		texture->SetFilter(GL_NEAREST, GL_NEAREST);
		texture->SetWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->GetTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetTextureID(), 0);
	}
	else
	{
		unsigned int depth;
		glGenRenderbuffers(1, &depth);
		glBindRenderbuffer(GL_RENDERBUFFER, depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->GetTextureID(), 0);
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);
	}
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		SDL_Log("Failed ot Create mirror buffer");
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

FrameBuffer::~FrameBuffer()
{
	if(frameBufferID!=0)
	{
		glDeleteFramebuffers(1, &frameBufferID);
	}
}
