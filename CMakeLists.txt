cmake_minimum_required(VERSION 3.28)
project(MyProject)

set(BENCHPP_MINIMUM_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Must be here before any things are done

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${BENCHPP_MINIMUM_CXX_STANDARD})
elseif(CMAKE_CXX_STANDARD LESS ${BENCHPP_MINIMUM_CXX_STANDARD})
  message(FATAL_ERROR "c++ standard set too low: ${CMAKE_CXX_STANDARD}. Need 17 or higher")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHPP_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE STRING "the")

add_subdirectory(src)

#build options
option(BENCHPP_DEBUG 
  "Add some extra debugging and asserts etc." 
  OFF
)

option(BENCHPP_TEST
  "Build the unitests, use the build.sh in build/validation for this" 
  OFF
)

option(BENCHPP_SAMPLES
  "Build the samples, use the build.sh in build/samples for this"
  OFF
)

#config options
option(BENCHPP_USE_HIGH_RESOLUTION_CLOCK
  "Use std::chrono::high_resolution as opposed to std::chronon::steady"
  OFF
)

function(benchpp_add_core_library TARGET_NAME)

  add_library(${TARGET_NAME})

  target_sources(${TARGET_NAME} 
    PUBLIC
      FILE_SET CXX_MODULES FILES
        ${BENCHPP_CORE_INTERFACE}
    PRIVATE
      ${BENCHPP_SOURCES}
  )

  target_include_directories(${TARGET_NAME}
    PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/include
  )


  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(${TARGET_NAME}
      PRIVATE
        ${BENCHPP_LINUX_SOURCES}
    )
  endif()

  target_include_directories(${TARGET_NAME}
    PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/private
  )

  if(BENCHPP_DEBUG)
    target_compile_definitions(${TARGET_NAME}
      PRIVATE
        NDEBUG
    )
  endif()

endfunction()

benchpp_add_core_library(benchpp)
benchpp_add_core_library(benchpp_with_main)

target_sources(benchpp_with_main
  PRIVATE
    src/main.cpp
)

if(BENCHPP_TEST)
  enable_testing()
  include(CTest)
  add_subdirectory(extern/catch2)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/Catch2/extras")
  include(Catch)

  add_subdirectory(validation)
endif()

if(BENCHPP_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()
