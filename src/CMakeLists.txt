set(BENCHPP_SOURCES
  src/timer.cpp
  src/mem/mem.cpp
  src/cache/cache.cpp
  src/core_metrics/core_metrics.cpp
  src/iteration_counter.cpp
  src/registry.cpp
  src/private/registry.cpp
  src/private/cli.cpp
  PARENT_SCOPE
)

set(BENCHPP_CORE_INTERFACE
  src/core.cppm
  src/cache/cache.cppm
  PARENT_SCOPE
)

set(BENCHPP_LINUX_SOURCES
  src/linux/perf_event.cpp
  src/linux/statusFile.cpp
  src/cache/linux/cache.cpp
  PARENT_SCOPE
)
