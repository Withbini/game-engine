include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# ExternalProject_Add(
#     dep-spdlog
#     GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
#     GIT_TAG "v1.x"
#     GIT_SHALLOW 1
#     UPDATE_COMMAND ""
#     PATCH_COMMAND ""
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
#     TEST_COMMAND ""
# )
# # Dependency 리스트 및 라이브러리 파일 리스트 추가
# set(DEP_LIST ${DEP_LIST} dep-spdlog)
# set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)

ExternalProject_Add(
	dep-SDL
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
	GIT_TAG "main"
	GIT_SHALLOW 1
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
	TEST_COMMAND ""
)
set(DEP_LIST ${DEP_LIST} dep-SDL)
set(DEP_LIBS ${DEP_LIBS} SDL)

ExternalProject_Add(
	dep-SDL_image
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image"
	GIT_TAG "main"
	GIT_SHALLOW 1
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
	TEST_COMMAND ""
)
set(DEP_LIST ${DEP_LIST} dep-SDL_image)
set(DEP_LIBS ${DEP_LIBS} SDL_image)

# glad
# ExternalProject_Add(
#     dep-glad
#     GIT_REPOSITORY "https://github.com/Dav1dde/glad"
#     GIT_TAG "v0.1.36"
#     GIT_SHALLOW 1
#     UPDATE_COMMAND ""
#     PATCH_COMMAND ""
#     CMAKE_ARGS
#         -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
#         -DGLAD_INSTALL=ON
#     TEST_COMMAND ""
#     )
# set(DEP_LIST ${DEP_LIST} dep-glad)
# set(DEP_LIBS ${DEP_LIBS} glad)

add_library(imgui
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_opengl3.cpp
    )
target_include_directories(imgui PRIVATE ${DEP_INCLUDE_DIR})
add_dependencies(imgui ${DEP_LIST})
set(DEP_INCLUDE_DIR ${DEP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(DEP_LIST ${DEP_LIST} imgui)
set(DEP_LIBS ${DEP_LIBS} imgui)