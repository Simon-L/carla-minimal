cmake_minimum_required(VERSION 3.15)
project(carla-minimal)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DDEBUG)
add_subdirectory(Carla/cmake)

add_executable(hello main.cpp
  carla_host.cpp)

target_include_directories(hello PUBLIC Carla/source/backend)
target_include_directories(hello PUBLIC Carla/source/includes)
target_include_directories(hello PUBLIC Carla/source/utils)

target_link_libraries(hello PUBLIC carla-standalone)
