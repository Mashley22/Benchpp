#ifndef BENCHPP_DETAIL_LINUX_CACHE_HPP
#define BENCHPP_DETAIL_LINUX_CACHE_HPP

#ifndef BENCHPP_DETAIL_LINUX_HEADER
#define BENCHPP_DETAIL_LINUX_HEADER
#endif

#include <Bench++/cache.hpp>
#include <Bench++/detail/linux/core.hpp>

#include <syscall.h>

#include <cstdint>

namespace benchpp {

namespace cache {

namespace detail {

namespace lnx {

[[nodiscard]] inline
int
open_cache_event(const Event& evt, pid_t pid = 0, int cpu = -1, int group_fd = -1, long unsigned flags = 0) {

  struct perf_event_attr hw_event = default_perf_event_attr();
    
  hw_event.type = PERF_TYPE_HW_CACHE; // SUPER IMPORTANT
  hw_event.config = create_cache_config(evt);
  
  return open_perf_event(hw_event, pid, cpu, group_fd, flags);
}

}

}

template<Event T_evt>
class Counter {
public:
  Counter(void) {
    m_fd = detail::lnx::open_cache_event(T_evt);
  }

  ~Counter(void) {
    if (m_fd != -1) {
      ioctl(m_fd, PERF_EVENT_IOC_DISABLE, 0); // double disable is safe i think?
      close(m_fd);
    }
  }
  
  [[nodiscard]]
  std::uint64_t
  read(void) {
    std::uint64_t count = detail::lnx::read_counter(m_fd);
    std::uint64_t delta{count - m_prev_val};
    m_prev_val = count;
    return delta;
  }

  void
  start(void) {
    detail::lnx::reset_counter(m_fd);
    detail::lnx::start_counter(m_fd);
  }
  
  void
  stop(void) {
    detail::lnx::stop_counter(m_fd);
  }

  [[nodiscard]]
  Type
  type(void) const noexcept {
    return T_evt.type;
  }

  [[nodiscard]]
  Operation
  operation(void) const noexcept {
    return T_evt.op;
  }

  [[nodiscard]]
  Result
  result(void) const noexcept {
    return T_evt.res;
  }

private:
  std::uint64_t m_prev_val{0};
  int m_fd{-1};
};

}

}

#endif /* BENCHPP_DETAIL_LINUX_CACHE_HPP */
