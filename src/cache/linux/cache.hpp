#include <Bench++/cache.hpp>

#include <Bench++/private/linux/perf_event.hpp>

#include <sys/ioctl.h>
#include <unistd.h>

#include <cassert>

namespace benchpp {

namespace cache {

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

[[nodiscard]]
int
M_open_cache_event(const Event& evt, pid_t pid = 0, int cpu = -1, int group_fd = -1, long unsigned flags = 0) { // NOLINT

  struct perf_event_attr hw_event = priv::lnx::default_perf_event_attr();
    
  hw_event.type = PERF_TYPE_HW_CACHE; // SUPER IMPORTANT
  hw_event.config = M_create_cache_config(evt);
  
  return priv::lnx::open_perf_event(hw_event, pid, cpu, group_fd, flags);
}

}

}

template<Event T_evt>
Counter<T_evt>::Counter(void) {
  m_::fd = lnx::M_open_cache_event(T_evt);
}

template<Event T_evt>
Counter<T_evt>::~Counter(void) {
  if (m_::fd != -1) {
    ioctl(m_::fd, PERF_EVENT_IOC_DISABLE, 0); // double disable is safe i think?
    close(m_::fd);
  }
}
  
template<Event T_evt>
[[nodiscard]]
std::int64_t
Counter<T_evt>::read(void) {
  assert(m_::fd != -1 && m_::isRunning == true);
  std::int64_t count = priv::lnx::read_counter(m_::fd);
  std::int64_t delta{count - m_::prev_val};
  m_::prev_val = count;
  return delta;
}

template<Event T_evt>
void
Counter<T_evt>::start(void) {
  assert(m_::fd != -1 && m_::isRunning == false);
  priv::lnx::reset_counter(m_::fd);
  priv::lnx::start_counter(m_::fd);
  m_::isRunning = true;
}
  
template<Event T_evt>
void
Counter<T_evt>::stop(void) {
  assert(m_::isRunning == true);
  priv::lnx::stop_counter(m_::fd);
  m_::isRunning = false;
}

}

}

