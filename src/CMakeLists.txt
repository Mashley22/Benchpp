set(BENCHPP_SOURCES
  src/timer.cpp
  src/mem/mem.cpp
  src/cache/cache.cpp
  src/core_metrics/core_metrics.cpp
  src/registry.cpp
  src/private/registry.cpp
  PARENT_SCOPE
)

set(BENCHPP_LINUX_SOURCES
  src/linux/perf_event.cpp
  src/linux/statusFile.cpp
  PARENT_SCOPE
)
