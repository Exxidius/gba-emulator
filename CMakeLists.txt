cmake_minimum_required(VERSION 4.0)

project(
  GBAemulator
  VERSION 0.1
  LANGUAGES CXX
)

set(CXX_STANDARD 26)

set(
  SOURCES
  src/main.cpp
)

include_directories(src)

add_executable(GBAemulator ${SOURCES})
