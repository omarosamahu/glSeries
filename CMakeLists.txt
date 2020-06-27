cmake_minimum_required(VERSION 3.10.2)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(OpenGl REQUIRED)

add_subdirectory(lib/glfw)
#add_subdirectory(lib/glew/build/cmake)


if(WIN32)
	list(APPEND EXTRA_LIBS
    "-lglu32 -lopengl32")
else()
	list(APPEND EXTRA_LIBS
		"-lGL -lGLU -lX11")
endif()
add_executable(video-app src/main.cpp 
						 src/Renderer.cpp
						 src/VertexBuffer.cpp
						 src/IndexBuffer.cpp)
#target_link_libraries(video-app glfw glew ${OPENGL_LIBRARIES} ${EXTRA_LIBS})

target_link_libraries(video-app glfw ${OPENGL_LIBRARIES}  ${GLEW_LIBRARIES} ${EXTRA_LIBS})
target_include_directories(video-app 
							PUBLIC
							${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(video-app ${GLEW_INCLUDE_DIRS})