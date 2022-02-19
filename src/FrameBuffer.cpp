#include "FrameBuffer.hpp"

FrameBufferUPtr FrameBuffer::Create(const std::vector<TexturePtr>& colorAttachments)
{
    auto buffer = FrameBufferUPtr(new FrameBuffer);
    if(buffer->Init(colorAttachments))
        return std::move(buffer);
    return nullptr;
}

void FrameBuffer::BindTextures() const
{
    for(auto i = 0; i < mColorAttachments.size(); ++i)
    {
        mColorAttachments[i]->Bind(i);
    }
    //glActiveTexture(GL_TEXTURE0);
}

void FrameBuffer::ReadBuffer() const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBufferID);
	debug("readbuffer");
}

bool FrameBuffer::Init(const std::vector<TexturePtr>& colorAttachments)
{
    mColorAttachments = colorAttachments;
    glGenFramebuffers(1, &frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

    unsigned int depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, colorAttachments[0]->GetWidth(), colorAttachments[0]->GetHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    vector<GLenum> drawBuffers;
    drawBuffers.resize(colorAttachments.size());
    for(int i = 0; i < colorAttachments.size(); ++i)
    {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorAttachments[i]->GetTextureID(), 0);
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
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
    if(frameBufferID != 0)
    {
        glDeleteFramebuffers(1, &frameBufferID);
    }
}
