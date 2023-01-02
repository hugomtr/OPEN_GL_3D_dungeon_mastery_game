cmake_minimum_required(VERSION 3.20)
project(OpenGLDungeonMastery)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/freetype)

find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
	include_directories(${ASSIMP_INCLUDE_DIR})
endif()
find_package(SFML COMPONENTS audio REQUIRED)

add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SOURCES_FILES CONFIGURE_DEPENDS src/*)
add_executable(OpenGLDungeonMastery main.cpp ${SOURCES_FILES})

target_include_directories(OpenGLDungeonMastery PRIVATE lib/)

target_link_libraries(OpenGLDungeonMastery
	PRIVATE
	glad
	glfw
	glm
	freetype
	sfml-audio
	${ASSIMP_LIBRARIES}
	OpenGL::GL)
