#include <Bench++/core_metrics.hpp>

#include <Bench++/private/linux/perf_event.hpp>

namespace benchpp {

namespace lnx {

namespace {

[[nodiscard]]
perf_event_attr
M_perf_event_attr(const Metric& val) noexcept {
  perf_event_attr retval = priv::lnx::default_perf_event_attr();

  switch (val) {
    case Metric::HW_CPU_CYCLES:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_REF_CPU_CYCLES;
      break;

    case Metric::BRANCH_INSTRUCTIONS:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
      break;
  
    case Metric::BRANCH_MISSES:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_BRANCH_MISSES;
      break;

    case Metric::CACHE_REFERENCES:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_CACHE_REFERENCES;
      break;

    case Metric::CACHE_MISSES:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_CACHE_MISSES;
      break;

    case Metric::STALLED_CYCLES_FRONTEND:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND;
      break;

    case Metric::STALLED_CYCLES_BACKEND:
      retval.type = PERF_TYPE_HARDWARE;
      retval.config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND;
      break;

    case Metric::CPU_MIGRATIONS:
      retval.type = PERF_TYPE_SOFTWARE;
      retval.config = PERF_COUNT_SW_CPU_MIGRATIONS;
      break;

    case Metric::CONTEXT_SWITCHES:
      retval.type = PERF_TYPE_SOFTWARE;
      retval.config = PERF_COUNT_SW_CONTEXT_SWITCHES;
      break;

    case Metric::PAGE_FAULTS:
      retval.type = PERF_TYPE_SOFTWARE;
      retval.config = PERF_COUNT_SW_PAGE_FAULTS;
      break;

    default:
      break;
  }
  return retval;
}

[[nodiscard]]
int
M_open_perf_event(const Metric& metric, pid_t pid = 0, int cpu = -1, int group_fd = -1, long unsigned flags = 0) { // NOLINT
  return priv::lnx::open_perf_event(M_perf_event_attr(metric), pid, cpu, group_fd, flags);
}

}

}

}
