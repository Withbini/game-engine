#pragma once
#include <string>
#include "Common.hpp"

CLASS_PTR(Image)
class Image
{
public:
	static ImageUPtr Load(const std::string& file);
	~Image();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	int GetChannel() const { return mChannel; }
	unsigned char* GetData() const { return mData; }
private:
	Image(){}
	bool LoadWithSOIL(const std::string& file);
	
	int mWidth {0};
	int mHeight {0};
	int mChannel {0};
	unsigned char* mData {nullptr};
};

