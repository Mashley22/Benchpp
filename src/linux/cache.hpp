#include <Bench++/linux/cache.hpp>


namespace benchpp {

namespace cache {

namespace detail {

namespace lnx {

int
open_cache_event(const Event& evt, pid_t pid, int cpu, int group_fd, long unsigned flags) { // NOLINT

  struct perf_event_attr hw_event = benchpp::detail::lnx::default_perf_event_attr();
    
  hw_event.type = PERF_TYPE_HW_CACHE; // SUPER IMPORTANT
  hw_event.config = detail::lnx::create_cache_config(evt);
  
  return benchpp::detail::lnx::open_perf_event(hw_event, pid, cpu, group_fd, flags);
}

}

}

}

}
