set(BENCHPP_SOURCES
  src/timer.cpp
  src/cache/cache.cpp
  src/core_metrics/core_metrics.cpp
  src/iteration_counter.cpp
  src/registry.cpp
  src/private/registry.cpp
  src/private/cli.cpp
  PARENT_SCOPE
)

set(BENCHPP_LINUX_SOURCES
  src/linux/perf_event.cpp
  src/linux/statusFile.cpp
  src/cache/linux/cache.cpp
  src/mem/linux/mem.cpp
  PARENT_SCOPE
)
