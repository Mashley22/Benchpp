cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(BENCHPP_MINIMUM_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Must be here before any things are done

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${BENCHPP_MINIMUM_CXX_STANDARD})
elseif(CMAKE_CXX_STANDARD LESS ${BENCHPP_MINIMUM_CXX_STANDARD})
  message(FATAL_ERROR "c++ standard set too low: ${CMAKE_CXX_STANDARD}. Need 17 or higher")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHPP_SOURCES
  src/timer.cpp
  src/mem/mem.cpp
  src/cache/cache.cpp
)

add_library(benchpp
  STATIC
    ${BENCHPP_SOURCES}
)

target_include_directories(benchpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(BENCHPP_LINUX_SOURCES
    src/linux/perf_event.cpp
    src/linux/statusFile.cpp
  )

  target_sources(benchpp
    PRIVATE
      ${BENCHPP_LINUX_SOURCES}
  )
  target_include_directories(benchpp
    PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/private
  )
endif()

#build options
option(BENCHPP_DEBUG 
  "Add some extra debugging and asserts etc." 
  OFF
)

option(BENCHPP_TEST
  "Build the unitests, use the build.sh in validation for this" 
  OFF
)

if(DEFINED BENCHPP_DEBUG)
  target_compile_definitions(benchpp
    PRIVATE
    NDEBUG
  )
endif()

#config options
option(BENCHPP_USE_HIGH_RESOLUTION_CLOCK
  "Use std::chrono::high_resolution as opposed to std::chronon::steady"
  OFF
)

if(DEFINED BENCHPP_TEST)
  enable_testing()
  include(CTest)
  add_subdirectory(extern/catch2)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/Catch2/extras")
  include(Catch)

  add_subdirectory(validation)
endif()
