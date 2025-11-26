#ifndef BENCHPP_CORE_METRICS_HPP
#define BENCHPP_CORE_METRICS_HPP

#include <string>
#include <cstdint>

#define BENCHPP_METRIC_ALL_GENERATOR(macro) \
    macro(benchpp::Metric::HW_CPU_CYCLES); \
    macro(benchpp::Metric::CACHE_REFERENCES); \
    macro(benchpp::Metric::CACHE_MISSES); \
    macro(benchpp::Metric::BRANCH_INSTRUCTIONS); \
    macro(benchpp::Metric::BRANCH_MISSES); \
    macro(benchpp::Metric::STALLED_CYCLES_FRONTEND); \
    macro(benchpp::Metric::STALLED_CYCLES_BACKEND); \
    macro(benchpp::Metric::PAGE_FAULTS); \
    macro(benchpp::Metric::CONTEXT_SWITCHES); \
    macro(benchpp::Metric::CPU_MIGRATIONS);

#define BENCHPP_METRIC_COUNTER_TEMPLATE_EXTENRN_DECL(met) extern template class MetricCounter<met>;

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
  Metric
  metric(void) const noexcept {
    return T_metric;
  }
private:
  using m_ = detail::Counter_impl;
};

BENCHPP_METRIC_ALL_GENERATOR(BENCHPP_METRIC_COUNTER_TEMPLATE_EXTENRN_DECL);

}

#endif /* BENCHPP_CORE_METRICS_HPP */
