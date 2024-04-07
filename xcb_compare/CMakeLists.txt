cmake_minimum_required(VERSION 3.20)

project(xcb_compare)

link_libraries(xcb)
link_libraries(X11)
add_executable(xcb_compare1 compare1.cpp)
add_executable(xcb_compare2 compare2.cpp)
add_executable(xcb_compare3 compare3.cpp)