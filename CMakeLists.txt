cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -DUSING_FLOAT64")

include_directories(./include)

find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})

file(GLOB MAIN_CPP main.cpp myvector.cpp)
add_executable(main ${MAIN_CPP})

file(GLOB TV_CPP test_vector.cpp myvector.cpp)
add_executable(test_vector ${TV_CPP})
