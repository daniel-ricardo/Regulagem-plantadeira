cmake_minimum_required(VERSION 3.14)
project(mainframe_base)
add_library(mainframe_base mainframe_base.cpp mainframe_base.hpp)

include_directories(${regulagem_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} regulagem)
