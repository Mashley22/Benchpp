module;

#include <linux/perf_event.h>
#include <sys/types.h>

export module Benchpp:priv.lnx.perf_event;

namespace benchpp {

namespace priv {

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
