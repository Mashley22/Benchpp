#ifndef BENCHPP_DETAIL_LINUX_CORE_METRICS_HPP
#define BENCHPP_DETAIL_LINUX_CORE_METRICS_HPP

#ifndef BENCHPP_DETAIL_LINUX_HEADER
#define BENCHPP_DETAIL_LINUX_HEADER
#endif

#include <Bench++/core_metrics.hpp>

#include <Bench++/detail/linux/core.hpp>

namespace benchpp {

namespace detail {

namespace lnx {

[[nodiscard]]
perf_event_attr
core_metric_perf_event_attr_struct(const Metric& metric) noexcept;

[[nodiscard]]
int 
open_core_metric_event(const Metric& metric,
                           pid_t pid = 0, int cpu = -1, int group_fd = -1, long unsigned flags = 0);


}

}

}

#endif /* BENCHPP_DETAIL_LINUX_CORE_METRICS_HPP */
