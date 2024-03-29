cmake_minimum_required(VERSION 3.20.0)

project(manager VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main foo.cpp thread.cpp manager.cpp main.cpp)
target_link_libraries(main PUBLIC X11 pthread)
