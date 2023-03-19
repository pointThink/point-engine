cmake_minimum_required(VERSION 3.20.0)

project(PointEngine)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB_RECURSE SOURCE_CPP source/PointEngine/*.cpp)
FILE(GLOB_RECURSE HEADER_CPP source/PointEngine/*.h)

add_compile_definitions(WINDOWS64 ENGINE_BUILD)

# imgui
FILE(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
include_directories(vendor/imgui)

add_library(pointengine SHARED ${SOURCE_CPP} ${HEADER_CPP} ${IMGUI_SOURCES} ${IMGUI_BACKEND} vendor/imgui/backends/imgui_impl_sdl2.cpp vendor/imgui/backends/imgui_impl_sdlrenderer.cpp)

set_target_properties(pointengine PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(pointengine PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

# add required libraries
# SDL2
add_subdirectory(vendor/SDL)
include_directories(vendor/SDL/include)
include_directories(vendor/SDL/include)
target_link_libraries(pointengine SDL2)

#SDL_image
add_subdirectory(vendor/SDL_image)
include_directories(vendor/SDL_image)
target_link_libraries(pointengine SDL2_image)

# openal soft
add_subdirectory(vendor/openal-soft)
include_directories(vendor/openal-soft/include)
target_link_libraries(pointengine common)
target_link_libraries(pointengine ex-common)
target_link_libraries(pointengine OpenAL)

target_include_directories(pointengine PUBLIC source)

# create an include directory withall the headers
