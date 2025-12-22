set(BENCHPP_SOURCES
  timer.cpp
  cache/cache.cpp
  core_metrics/core_metrics.cpp
  iteration_counter.cpp
  registry.cpp
  cli.cpp
  private/registry.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(BENCHPP_SYSTEM_SOURCES
    linux/perf_event.cpp
    linux/statusFile.cpp
    cache/linux/cache.cpp
    mem/linux/mem.cpp
    core_metrics/linux/core_metrics.cpp
  )
endif()

list(APPEND BENCHPP_SOURCES ${BENCHPP_SYSTEM_SOURCES})

list(TRANSFORM BENCHPP_SOURCES PREPEND "src/")
