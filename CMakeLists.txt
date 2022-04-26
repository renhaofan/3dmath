cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -DUSING_FLOAT64")

include_directories(./include)

file(GLOB SRC_CPP "*.cpp")
add_executable(3dmath ${SRC_CPP})
