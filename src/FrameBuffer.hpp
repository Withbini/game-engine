#pragma once
#include "Common.hpp"
#include "Texture.hpp"

CLASS_PTR(FrameBuffer)
class FrameBuffer
{
public:
    static FrameBufferUPtr Create(const std::vector<TexturePtr>& colorAttachments);

    virtual ~FrameBuffer();
    unsigned GetFrameBufferID() const { return frameBufferID; }
    TexturePtr GetTexture(int index = 0) const { return mColorAttachments[index]; } //TODO :change to texture ptr
    size_t GetTextureSize() const { return mColorAttachments.size(); }
    void BindTextures() const;
	void ReadBuffer() const;
protected:
    virtual bool Init(const std::vector<TexturePtr>& colorAttachments);

    unsigned int frameBufferID { 0 };
    vector<TexturePtr> mColorAttachments;
private:
    FrameBuffer() = default;
};

