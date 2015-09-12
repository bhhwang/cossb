################################
# COSSB CMakeList.txt
################################

cmake_minimum_required(VERSION 2.8)
project(cossb)

include_directories(${cossb_SOURCE_DIR}/include)

set (INCLUDE_DIR ${cossb_SOURCE_DIR}/include)
set (EXAMPLE_DIR ${cossb_SOURCE_DIR}/example)
set (LIB_DIR ${cossb_SOURCE_DIR}/lib)
set (SUPPORT_DIR ${cossb_SOURCE_DIR}/support)
set (TEST_DIR ${cossb_SOURCE_DIR}/test)
set (SOURCE_DIR ${cossb_SOURCE_DIR}/src)

add_executable(cossb ${SOURCE_DIR}/engine.cpp)
add_executable(cossbd ${SOURCE_DIR}/engined.cpp)