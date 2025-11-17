cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(BENCHPP_MINIMUM_CXX_STANDARD 17)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${BENCHPP_MINIMUM_CXX_STANDARD})
elseif(CMAKE_CXX_STANDARD LESS BENCHPP_MINIMUM_CXX_STANDARD)
  message(FATA_ERROR "c++ standard set too low: ${CMAKE_CXX_STANDARD}. Need 17 or higher")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
add_subdirectory(extern/catch2)
