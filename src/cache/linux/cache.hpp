#include <Bench++/linux/cache.hpp>


namespace benchpp {

namespace cache {

namespace detail {

namespace lnx {

namespace {

[[nodiscard]]
std::uint64_t 
M_create_cache_config(const Event& evt) noexcept { // NOLINT
  uint64_t cache_val, op_val, result_val;
  
  switch (evt.type) {
    case Type::L1D:  cache_val = PERF_COUNT_HW_CACHE_L1D; break;
    case Type::L1I:  cache_val = PERF_COUNT_HW_CACHE_L1I; break;
    case Type::LL:   cache_val = PERF_COUNT_HW_CACHE_LL; break;
    case Type::DTLB: cache_val = PERF_COUNT_HW_CACHE_DTLB; break;
    case Type::ITLB: cache_val = PERF_COUNT_HW_CACHE_ITLB; break;
    default:              cache_val = PERF_COUNT_HW_CACHE_L1D; break;
  }
  
  switch (evt.op) {
    case Operation::READ:     op_val = PERF_COUNT_HW_CACHE_OP_READ; break;
    case Operation::WRITE:    op_val = PERF_COUNT_HW_CACHE_OP_WRITE; break;
    case Operation::PREFETCH: op_val = PERF_COUNT_HW_CACHE_OP_PREFETCH; break;
    default:                       op_val = PERF_COUNT_HW_CACHE_OP_READ; break;
  }
  
  switch (evt.res) {
    case Result::ACCESS: result_val = PERF_COUNT_HW_CACHE_RESULT_ACCESS; break;
    case Result::MISS:   result_val = PERF_COUNT_HW_CACHE_RESULT_MISS; break;
    default:                  result_val = PERF_COUNT_HW_CACHE_RESULT_MISS; break;
  }
  
  return cache_val | (op_val << 8) | (result_val << 16);
}

}

int
open_cache_event(const Event& evt, pid_t pid, int cpu, int group_fd, long unsigned flags) { // NOLINT

  struct perf_event_attr hw_event = benchpp::detail::lnx::default_perf_event_attr();
    
  hw_event.type = PERF_TYPE_HW_CACHE; // SUPER IMPORTANT
  hw_event.config = detail::lnx::M_create_cache_config(evt);
  
  return benchpp::detail::lnx::open_perf_event(hw_event, pid, cpu, group_fd, flags);
}

}

}

}

}
