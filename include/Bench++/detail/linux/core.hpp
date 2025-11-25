#ifndef BENCHPP_DETAIL_LINUX_CORE_HPP
#define BENCHPP_DETAIL_LINUX_CORE_HPP

#ifndef BENCHPP_DETAIL_LINUX_HEADER
#define BENCHPP_DETAIL_LINUX_HEADER
#endif

#include <Bench++/cache.hpp>

#include <linux/perf_event.h>

#include <cstdint>

namespace benchpp {

namespace detail {

namespace lnx {

[[nodiscard]]
perf_event_attr
default_perf_event_attr(void);

[[nodiscard]]
int
open_perf_event(const perf_event_attr& hw_event, pid_t pid = 0, int cpu = -1, int group_fd = -1, unsigned long flags = 0);

void
reset_counter(int fd);

void
start_counter(int fd);

void
stop_counter(int fd);

[[nodiscard]]
long long
read_counter(int fd);

}

}

}


#endif /* BENCHPP_DETAIL_LINUX_CORE_HPP */
