#pragma once
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
//TODO: Change path
//#include "../imgui/imgui.h"
//#include <../imgui/imgui_impl_opengl3.h>
//#include <../imgui/imgui_impl_sdl.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;