cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Stack)
project(${PROJECT_NAME})

set(stacklib StackLib)
set(testlib GTest_Lib)
set(test TestMain)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GTestLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/StackLib)

add_subdirectory(StackLib)
add_subdirectory(gtest)
add_subdirectory(test)