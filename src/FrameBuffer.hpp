#pragma once
#include "Common.hpp"
#include "Texture.hpp"

CLASS_PTR(FrameBuffer)
class FrameBuffer
{
public:
	static FrameBufferUPtr Create(int width, int height, uint32_t format, uint32_t type);
	
	virtual ~FrameBuffer();
	unsigned GetFrameBufferID() const {return frameBufferID;}
	TexturePtr GetTexture() const { return texture; } //TODO :change to texture ptr
private:
	FrameBuffer() = default;
	bool Init(int width, int height, uint32_t format, uint32_t type);
	unsigned int frameBufferID {0};
	TexturePtr texture {nullptr};
};

