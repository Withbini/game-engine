#include "Image.hpp"

#include <SDL_log.h>
#include <SOIL.h>

Image::~Image()
{
	if(mData)
		SOIL_free_image_data(mData);
}

ImageUPtr Image::Load(const std::string& file)
{
	auto image = ImageUPtr(new Image);
	if(!image->LoadWithSOIL(file))
	{
		SDL_Log("SOIL failed to load image %s: %s", SOIL_last_result(), file.c_str());
		return nullptr;
	}
	return std::move(image);
}

bool Image::LoadWithSOIL(const std::string& file)
{
	mData = SOIL_load_image(file.c_str(), &mWidth, &mHeight, &mChannel, SOIL_LOAD_AUTO);
	if (mData == nullptr)
	{
		return false;
	}
	return true;
}