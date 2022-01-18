cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(OpenGL_Lesson)

set(CMAKE_CXX_STANDARD 23)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/glad)

add_executable(${PROJECT_NAME} main.cpp Lib/Shader.cpp Lib/Shader.h)

target_link_libraries(${PROJECT_NAME} glfw glad)

file(COPY Assets DESTINATION .)