#ifndef BENCHPP_DETAIL_LINUX_CACHE_HPP
#define BENCHPP_DETAIL_LINUX_CACHE_HPP

#ifndef BENCHPP_DETAIL_LINUX_HEADER
#define BENCHPP_DETAIL_LINUX_HEADER
#endif

#include <Bench++/cache.hpp>
#include <Bench++/detail/linux/core.hpp>

#include <syscall.h>

#include <cstdint>
#include <cassert>

namespace benchpp {

namespace cache {

namespace detail {

namespace lnx {

[[nodiscard]]
int
open_cache_event(const Event& evt, pid_t pid = 0, int cpu = -1, int group_fd = -1, long unsigned flags = 0);

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
  std::int64_t
  read(void) {
    assert(m_fd != -1 && m_isRunning == true);
    std::int64_t count = benchpp::detail::lnx::read_counter(m_fd);
    std::int64_t delta{count - m_prev_val};
    m_prev_val = count;
    return delta;
  }

  void
  start(void) {
    assert(m_fd != -1 && m_isRunning == false);
    benchpp::detail::lnx::reset_counter(m_fd);
    benchpp::detail::lnx::start_counter(m_fd);
    m_isRunning = true;
  }
  
  void
  stop(void) {
    assert(m_isRunning == true);
    benchpp::detail::lnx::stop_counter(m_fd);
    m_isRunning = false;
  }

  [[nodiscard]] constexpr
  Type
  type(void) const noexcept {
    return T_evt.type;
  }

  [[nodiscard]] constexpr
  Operation
  operation(void) const noexcept {
    return T_evt.op;
  }

  [[nodiscard]] constexpr
  Result
  result(void) const noexcept {
    return T_evt.res;
  }

  [[nodiscard]] constexpr
  const Event&
  event(void) const noexcept {
    return T_evt;
  }

private:
  std::int64_t m_prev_val{0};
  int m_fd{-1};
  bool m_isRunning{false};
};

}

}

#endif /* BENCHPP_DETAIL_LINUX_CACHE_HPP */
