set(BENCHPP_PUBLIC_PARTITIONS
  stats.cppm
  cache.cppm
  timer.cppm
  events.cppm
  mem/mem.cppm
  core_metrics.cppm
  iteration_counter.cppm
  registry.cppm
  cli.cppm
)

set(BENCHPP_PRIVATE_PARTITIONS
  registry.cppm
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(BENCHPP_PUBLIC_SYSTEM_PARTITIONS
    mem/linux/exception.cppm
  )
  set(BENCHPP_PRIVATE_SYSTEM_PARTITIONS
    linux/statusFile.cppm
    linux/perf_event.cppm
  )
endif()

list(APPEND BENCHPP_PUBLIC_PARTITIONS ${BENCHPP_PUBLIC_SYSTEM_PARTITIONS})
list(APPEND BENCHPP_PRIVATE_PARTITIONS ${BENCHPP_PRIVATE_SYSTEM_PARTITIONS})

list(TRANSFORM BENCHPP_PUBLIC_PARTITIONS PREPEND "modules/public/")
list(TRANSFORM BENCHPP_PRIVATE_PARTITIONS PREPEND "modules/private/")
