#pragma once
#include "Common.hpp"
#include "Texture.hpp"

CLASS_PTR(MirrorBuffer)
class MirrorBuffer
{
public:
    static MirrorBufferUPtr Create(const std::vector<TexturePtr>& colorAttachments);

    virtual ~MirrorBuffer();
    unsigned GetFrameBufferID() const { return mFrameBufferID; }
    TexturePtr GetTexture(int index = 0) const { return mColorAttachments[index]; } //TODO :change to texture ptr
protected:
    virtual bool Init(const std::vector<TexturePtr>& colorAttachments);

    unsigned int mFrameBufferID { 0 };
    vector<TexturePtr> mColorAttachments;
private:
    MirrorBuffer() = default;
};
