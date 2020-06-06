cmake_minimum_required(VERSION 3.10.2)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glew/build/cmake)

list(APPEND EXTRA_LIBS
    "-lGL -lGLU -lX11")

add_executable(video-app src/main.cpp)
target_link_libraries(video-app glfw glew ${EXTRA_LIBS})