#include "MirrorBuffer.hpp"

MirrorBufferUPtr MirrorBuffer::Create(const std::vector<TexturePtr>& colorAttachments)
{
    auto buffer = MirrorBufferUPtr(new MirrorBuffer);
    if(buffer->Init(colorAttachments))
        return std::move(buffer);
    return nullptr;
}

bool MirrorBuffer::Init(const std::vector<TexturePtr>& colorAttachments)
{
    mColorAttachments = colorAttachments;
    glGenFramebuffers(1, &mFrameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferID);

    unsigned int depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, colorAttachments[0]->GetWidth(), colorAttachments[0]->GetHeight());
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

MirrorBuffer::~MirrorBuffer()
{
    if(mFrameBufferID != 0)
    {
        glDeleteFramebuffers(1, &mFrameBufferID);
    }
}
