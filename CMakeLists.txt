cmake_minimum_required(VERSION 3.20.0)

project(PointEngine-Core)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB_RECURSE SOURCE_CPP source/PointEngine/*.cpp)
FILE(GLOB_RECURSE HEADER_CPP source/PointEngine/*.h)

# source_group("Header files" FILES {HEADER_CPP})
add_compile_definitions(WINDOWS64 ENGINE_BUILD)

# imgui
FILE(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
source_group("imgui" FILES ${IMGUI_SOURCES} ${IMGUI_BACKEND})
include_directories(vendor/imgui)

add_library(pointengine-core SHARED ${SOURCE_CPP} ${HEADER_CPP} ${IMGUI_SOURCES} ${IMGUI_BACKEND} vendor/imgui/backends/imgui_impl_sdl2.cpp vendor/imgui/backends/imgui_impl_sdlrenderer.cpp)

# set_target_properties(pointengine PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(pointengine-core PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

# add required libraries
# SDL2
add_subdirectory(vendor/SDL)
#add_dependencies(pointengine-core SDL)
include_directories(vendor/SDL/include)
include_directories(vendor/SDL/include)
target_link_libraries(pointengine-core SDL2)
set_target_properties(SDL2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

#SDL_image
add_subdirectory(vendor/SDL_image)
#add_dependencies(pointengine-core SDL_image)
include_directories(vendor/SDL_image)
target_link_libraries(pointengine-core SDL2_image)
set_target_properties(SDL2_image PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

# SDL_ttf
add_subdirectory(vendor/SDL_ttf)
#add_dependencies(pointengine-core SDL_image)
include_directories(vendor/SDL2_ttf)
target_link_libraries(pointengine-core SDL2_ttf)
set_target_properties(SDL2_ttf PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

target_include_directories(pointengine-core PRIVATE source)

# set(GENERATED_HEADER_DIR include)

# add_custom_command(TARGET pointengine-core POST_BUILD COMMAND post_build.bat)

# make the test game
FILE(GLOB GAME_SOURCES_CPP source/game/*.cpp)
FILE(GLOB GAME_HEADERS_CPP source/game/*.h)

add_compile_definitions(WINDOWS64)
set(CMAKE_CXX_STANDARD 20)

add_executable(game ${GAME_SOURCES_CPP} ${GAME_HEADERS_CPP})
target_link_libraries(game pointengine-core)
include_directories(source/PointEngine/)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)