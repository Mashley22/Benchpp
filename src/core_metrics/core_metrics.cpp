module;

#include <string>

module Benchpp;

namespace benchpp {

[[nodiscard]]
std::string metric_toStr(const Metric& metric) {
  switch (metric) {
    case Metric::HW_CPU_CYCLES:
      return "HW_CPU_CYCLES";
    case Metric::CACHE_REFERENCES:
      return "CACHE_REFERENCES";
    case Metric::CACHE_MISSES:
      return "CACHE_MISSES";
    case Metric::BRANCH_INSTRUCTIONS:
      return "BRANCH_INSTRUCTIONS";
    case Metric::BRANCH_MISSES:
      return "BRANCH_MISSES";
    case Metric::STALLED_CYCLES_FRONTEND:
      return "STALLED_CYCLES_FRONTEND";
    case Metric::STALLED_CYCLES_BACKEND:
      return "STALLED_CYCLES_BACKEND";
    case Metric::PAGE_FAULTS:
      return "PAGE_FAULTS";
    case Metric::CONTEXT_SWITCHES:
      return "CONTEXT_SWITCHES";
    case Metric::CPU_MIGRATIONS:
      return "CPU_MIGRATIONS";
  }
  return "Invalid Metric";
}

}
