cmake_minimum_required(VERSION 4.0)

project(
  GBAemulator
  VERSION 0.1
  LANGUAGES CXX
)

set(CXX_STANDARD 26)

find_package(SDL3 REQUIRED CONFIG)

set(
  SOURCES
  src/main.cpp
  src/imgui/imgui.cpp
  src/imgui/imgui_draw.cpp
  src/imgui/imgui_tables.cpp
  src/imgui/imgui_widgets.cpp
  src/imgui/imgui_impl_sdl3.cpp
  src/imgui/imgui_impl_sdlrenderer3.cpp
)

include_directories(src)

add_executable(GBAemulator ${SOURCES})
target_link_libraries(GBAemulator PRIVATE SDL3::SDL3)
