cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(OpenGL_Lesson)

set(CMAKE_CXX_STANDARD 23)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/glad)

add_executable(${PROJECT_NAME} main.cpp Lib/Shader.cpp Lib/Shader.h Dependencies/stb_image.cpp)

target_link_libraries(${PROJECT_NAME} glfw glad)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/Assets"      # <--this is in-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets)