cmake_minimum_required(VERSION 3.20.0)

macro(ADD_SUBDIR subdir)
	FILE(GLOB children RELATIVE ${subdir} ${subdir}/*)

	file(GLOB NEW_SRC "source/${subdir}/*.cpp")
	file(GLOB NEW_HEADER "source/${subdir}/*.h")

	source_group("source/${subdir}" FILES ${NEW_SRC})
	source_group("source/${subdir}" FILES ${NEW_HEADER})
endmacro()

project(PointEngine-Core)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT DEFINED PE_OutputPath)
	set(PE_OutputPath bin)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB_RECURSE PE_SRC source/PointEngine/*.cpp)
FILE(GLOB_RECURSE PE_HEADERS source/PointEngine/*.h)

add_compile_definitions(WINDOWS64 ENGINE_BUILD)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message("Using MSVC")
	add_compile_definitions(COMP_MSVC)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message("Using GCC")
	add_compile_definitions(COMP_GCC)
endif()

# imgui

FILE(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
# set(IMGUI_BACKEND vendor/imgui/backends/imgui_impl_sdl2.cpp vendor/imgui/backends/imgui_impl_sdlrenderer.cpp)

source_group("vendor/imgui" FILES ${IMGUI_SOURCES} ${IMGUI_BACKEND})
include_directories(vendor/imgui)

# glad
set(GLAD_FILE vendor/glad/src/glad.c)
include_directories(vendor/glad/include)

source_group("vendor/glad" FILES ${GLAD_FILE})

# stb_image
set(STBI_FILE vendor/stb_image/stb_image.cpp)
include_directories(vendor/stb_image/)

source_group("vendor/stb_image" FILES ${STBI_FILE})


ADD_SUBDIR(PointEngine)
ADD_SUBDIR(PointEngine/Rendering)
ADD_SUBDIR(PointEngine/Entity)
ADD_SUBDIR(PointEngine/Console)
ADD_SUBDIR(PointEngine/Utils)
ADD_SUBDIR(PointEngine/Scripting)
ADD_SUBDIR(PointEngine/UI)
ADD_SUBDIR(PointEngine/Gamestate)
ADD_SUBDIR(PointEngine/Hardware)
ADD_SUBDIR(PointEngine/Error)
ADD_SUBDIR(PointEngine/Rendering/OpenGL)

#source_group("source" FILES ${PE_SRC})
#source_group("source" FILES ${PE_HEADERS})

include_directories(source/PointEngine)

add_library(pointengine-core SHARED ${PE_SRC} ${PE_HEADERS} ${IMGUI_SOURCES} ${IMGUI_BACKEND} ${GLAD_FILE} ${STBI_FILE})

# set_target_properties(pointengine PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(pointengine-core PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PE_OutputPath})

# glfw
add_subdirectory(vendor/glfw)

add_dependencies(pointengine-core glfw)
include_directories(vendor/glfw/include)
target_link_libraries(pointengine-core glfw)
set_target_properties(glfw PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../${PE_OutputPath})



set_target_properties(glfw PROPERTIES FOLDER dependencies)

# make the test game
if (PE_MakeTestGame)
	FILE(GLOB GAME_SOURCES_CPP source/TestGame/*.cpp)
	FILE(GLOB GAME_HEADERS_CPP source/TestGame/*.h)

	add_compile_definitions(WINDOWS64)
	set(CMAKE_CXX_STANDARD 20)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		message("Using MSVC")
		add_compile_definitions(COMP_MSVC)

	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message("Using GCC")
		add_compile_definitions(COMP_GCC)
	endif()

	add_executable(game ${GAME_SOURCES_CPP} ${GAME_HEADERS_CPP})
	target_link_libraries(game pointengine-core)
	include_directories(source/PointEngine/)

	set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PE_OutputPath})
endif()
