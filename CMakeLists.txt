cmake_minimum_required(VERSION 3.0.0)

project(PointEngine)

add_subdirectory(vendor/SDL)

add_library(pointengine SHARED *.cpp)