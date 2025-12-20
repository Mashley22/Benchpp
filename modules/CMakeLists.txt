set(BENCHPP_PUBLIC_PARTITIONS
  stats.cppm
  cache.cppm
  timer.cppm
  events.cppm
  mem.cppm
  mem/linux/exception.cppm
)

set(BENCHPP_PRIVATE_PARTITIONS
  linux/statusFile.cppm
)

list(TRANSFORM BENCHPP_PUBLIC_PARTITIONS PREPEND "modules/public/")
list(TRANSFORM BENCHPP_PRIVATE_PARTITIONS PREPEND "modules/private/")
