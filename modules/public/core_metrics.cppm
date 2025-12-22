module;

#include <string>
#include <cstdint>

export module Benchpp:core_metrics;

namespace benchpp {

export
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

export
[[nodiscard]]
std::string
metric_toStr(const Metric&);

namespace detail {
#ifdef __linux__
class LinuxCounter_impl {
protected:
  std::int64_t prev_val{0};
  int fd{-1};
  bool isRunning{false};
};
using Counter_impl = LinuxCounter_impl;
#endif /* __linux__ */

}

export
template<Metric T_metric>
class MetricCounter : detail::Counter_impl {
public:

  MetricCounter(void);

  ~MetricCounter(void);

  [[nodiscard]]
  std::int64_t
  read(void);

  void
  start(void);

  void
  stop(void);

  [[nodiscard]]
  bool
  isRunning(void) const noexcept {
    return detail::Counter_impl::isRunning;
  }

  [[nodiscard]]
  Metric
  metric(void) const noexcept {
    return T_metric;
  }

private:
  using m_ = detail::Counter_impl;
};


}
