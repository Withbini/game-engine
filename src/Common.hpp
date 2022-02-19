#pragma once
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>
//TODO: Change path
#include "../imgui/imgui.h"
#include <../imgui/imgui_impl_opengl3.h>
#include <../imgui/imgui_impl_sdl.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

using std::vector;
using std::string;

class Logger
{
public:
	static void Log(const char *funcName, int line, int level, const char* str, ...)
	{
		auto st = glGetError();
		if(st!=0)
			SDL_Log("%d %s %d level: %d %s", st, funcName, line, level, str);
	}
};
enum ELOG_LEVEL
{
	LOG_LEVEL_OFF= 0,
	LOG_LEVEL_FATAL= 10,
	LOG_LEVEL_ERROR= 20,
	LOG_LEVEL_WARN= 30,
	LOG_LEVEL_INFO= 40,
	LOG_LEVEL_DEBUG= 50,
	LOG_LEVEL_TRACE= 60,
	LOG_LEVEL_ALL= 100
};
#define fatal(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_FATAL, str, ##__VA_ARGS__)
#define error(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_ERROR, str, ##__VA_ARGS__)
#define warn(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_WARN, str, ##__VA_ARGS__)
#define info(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_INFO, str, ##__VA_ARGS__)
#define debug(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_DEBUG, str, ##__VA_ARGS__)
#define trace(str, ...) Logger::Log(__FUNCTION__, __LINE__, LOG_LEVEL_TRACE, str, ##__VA_ARGS__)

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	//glm::vec3 tangent;
};

static void BindBuffer(unsigned int id)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

static void SetViewport(float width,float height)
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}