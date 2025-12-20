set(BENCHPP_PUBLIC_PARTITIONS
  stats.cppm
  cache.cppm
  timer.cppm
  events.cppm
)

list(TRANSFORM BENCHPP_PUBLIC_PARTITIONS PREPEND "modules/public/")
