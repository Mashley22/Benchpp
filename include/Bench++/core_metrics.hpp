#ifndef BENCHPP_CORE_METRICS_HPP
#define BENCHPP_CORE_METRICS_HPP

#include <string>

#define BENCHPP_METRIC_ALL_GENERATOR(macro) \
    macro(Metric::HW_CPU_CYCLES); \
    macro(Metric::CACHE_REFERENCES); \
    macro(Metric::CACHE_MISSES); \
    macro(Metric::BRANCH_INSTRUCTIONS); \
    macro(Metric::BRANCH_MISSES); \
    macro(Metric::STALLED_CYCLES_FRONTEND); \
    macro(Metric::STALLED_CYCLES_BACKEND); \
    macro(Metric::PAGE_FAULTS); \
    macro(Metric::CONTEXT_SWITCHES); \
    macro(Metric::CPU_MIGRATIONS);

namespace benchpp {

enum class Metric {
  HW_CPU_CYCLES,
  CACHE_REFERENCES,
  CACHE_MISSES,
  BRANCH_INSTRUCTIONS,
  BRANCH_MISSES,
  STALLED_CYCLES_FRONTEND,
  STALLED_CYCLES_BACKEND,
  PAGE_FAULTS,
  CONTEXT_SWITCHES,
  CPU_MIGRATIONS
};

[[nodiscard]]
std::string
metric_toStr(const Metric&);

}

#endif /* BENCHPP_CORE_METRICS_HPP */
