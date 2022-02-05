cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME game)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Game")
set(WINDOW_WIDTH 1280)
set(WINDOW_HEIGHT 720)

project(${PROJECT_NAME})
file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB HEADER_FILES CONFIGURE_DEPENDS src/*.hpp)
file(GLOB SHADER_FILES CONFIGURE_DEPENDS src/shader/*.vert src/shader/*.frag)
file(GLOB EXAMPLE_FILES CONFIGURE_DEPENDS example/*.hpp example/*.cpp)
add_executable(${PROJECT_NAME} 
    ${SRC_FILES}
    ${HEARDER_FILES}
    ${SHADER_FILES}
    ${EXAMPLE_FILES}
)

include(Dependency.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/example)

target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME = "${WINDOW_NAME}"
    WINDOW_WIDTH = "${WINDOW_WIDTH}"
    WINDOW_HEIGHT = "${WINDOW_HEIGHT}"
)

add_dependencies(${PROJECT_NAME} ${DEP_LIST})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4819)
endif()