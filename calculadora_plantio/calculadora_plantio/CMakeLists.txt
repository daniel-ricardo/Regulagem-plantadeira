cmake_minimum_required(VERSION 3.14)
include(FetchContent)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(regular_plantadeira)
add_executable(${PROJECT_NAME} calculadora_plantio.cpp calculadora_plantio.hpp)

# biblioteca fmt:

set(FMT_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/fmt)
set(FMT_VERSION 10.0.0)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG ${FMT_VERSION}
)
FetchContent_MakeAvailable(fmt)

set(fmt_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/fmt-src")
list(APPEND CMAKE_PREFIX_PATH ${fmt_DIR})

include_directories(${fmtL_DIR}/include)
include_directories(${FMT_INSTALL_DIR}/include)
include_directories(${fmt_INCLUDE_DIRS})

set(WXWIDGETS_VERSION v3.2.2.1)

FetchContent_Declare(
  wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG ${WXWIDGETS_VERSION}
)
FetchContent_MakeAvailable(wxWidgets)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
set(wxWidgets_CONFIGURATION mswu)
include(${wxWidgets_USE_FILE})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/deps)

add_subdirectory(regulagem)
add_subdirectory(mainframe_base)

add_library(calculadora_plantio calculadora_plantio.cpp calculadora_plantio.hpp)

target_link_libraries(${PROJECT_NAME} regulagem)
target_link_libraries(${PROJECT_NAME} mainframe_base)
target_link_libraries(${PROJECT_NAME} calculadora_plantio)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

