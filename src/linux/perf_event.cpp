#include <Bench++/private/linux/perf_event.hpp>

#include <stdexcept>
#include <asm/unistd.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>

namespace benchpp {

namespace priv {

namespace lnx {

[[nodiscard]]
perf_event_attr
default_perf_event_attr(void) { // NOLINT
  struct perf_event_attr hw_event{}; // should be all 0 initialized??! check this!
  
  hw_event.disabled = 1;
  hw_event.exclude_kernel = 1;
  hw_event.exclude_hv = 1;

  return hw_event;
}

int
open_perf_event(const perf_event_attr& hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) { // NOLINT
  long retval = syscall(__NR_perf_event_open, &hw_event, pid, cpu, group_fd, flags);

  if (retval == -1) {
    throw std::runtime_error("Failed to open perf event err: " + std::to_string(retval));
  }

  return static_cast<int>(retval);
}

void
reset_counter(int fd) { // NOLINT
  long res = ioctl(fd, PERF_EVENT_IOC_RESET, 0);

  if (res == -1) {
    throw std::runtime_error("Failed to reset counter fd: " + std::to_string(fd));
  }
}

void
start_counter(int fd) { // NOLINT
  long res = ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

  if (res == -1) {
    throw std::runtime_error("Failed to start counter fd: " + std::to_string(fd));
  }
}

void
stop_counter(int fd) { // NOLINT
  long res = ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);

  if (res == -1) {
    throw std::runtime_error("Failed to disable counter fd: " + std::to_string(fd));
  }
}

long long
read_counter(int fd) { // NOLINT
  long long value;
  ssize_t res = ::read(fd, &value, sizeof(value));
  
  if (res == -1) {
    throw std::runtime_error("Failed to read counter fd: " + std::to_string(fd));
  }

  return value;
}

}

}

}
