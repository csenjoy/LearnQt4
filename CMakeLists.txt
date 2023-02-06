cmake_minimum_required(VERSION 3.5)
project(cppguiprogrammingwithqt4)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(ch1_GettingStart)
add_subdirectory(ch2_CreatingDialogs)
add_subdirectory(ch3_CreatingMainWindow)

add_subdirectory(ch08_2DGraphics)