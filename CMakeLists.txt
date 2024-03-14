cmake_minimum_required(VERSION 3.20.0)
project(connection VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
add_executable(main main.cpp)
target_link_libraries(main X11)

target_sources(main PRIVATE tile_stipple.cpp)