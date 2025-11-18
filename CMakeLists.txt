cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(BENCHPP_MINIMUM_CXX_STANDARD 20)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${BENCHPP_MINIMUM_CXX_STANDARD})
elseif(CMAKE_CXX_STANDARD LESS ${BENCHPP_MINIMUM_CXX_STANDARD})
  message(FATAL_ERROR "c++ standard set too low: ${CMAKE_CXX_STANDARD}. Need 17 or higher")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHPP_SOURCES
      src/timer.cpp
)

add_library(benchpp
  STATIC
    ${BENCHPP_SOURCES}
)

target_include_directories(benchpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

option(BENCHPP_DEBUG "Add some extra debugging and asserts etc." OFF)

option(BENCHPP_TEST "Build the unitests, use the build.sh in validation for this" OFF)

if(DEFINED BENCHPP_TEST)
  enable_testing()
  include(CTest)
  add_subdirectory(extern/catch2)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/Catch2/extras")
  include(Catch)

  add_subdirectory(validation)
endif()
