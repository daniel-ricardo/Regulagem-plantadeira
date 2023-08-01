cmake_minimum_required(VERSION 3.14)
include(FetchContent)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(regular_plantadeira)
add_executable(${PROJECT_NAME} calculadora_plantio.cpp calculadora_plantio.hpp)

FetchContent_Declare(
  wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG v3.2.2.1
)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(wxWidgets fmt)

find_package(wxWidgets REQUIRED COMPONENTS net core base xrc xml html adv aui)
set(wxWidgets_CONFIGURATION mswu)

include(${wxWidgets_USE_FILE})

add_subdirectory(regulagem)
add_subdirectory(mainframe_base)

add_library(calculadora_plantio calculadora_plantio.cpp calculadora_plantio.hpp)

target_link_libraries(${PROJECT_NAME} regulagem)
target_link_libraries(${PROJECT_NAME} mainframe_base)
target_link_libraries(${PROJECT_NAME} calculadora_plantio)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
