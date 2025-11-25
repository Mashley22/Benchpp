#include <Bench++/detail/linux/core.hpp>

#include <stdexcept>

#ifndef __linux__
#error "Only build this file if on linux"
#endif 

namespace benchpp {

namespace detail {

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

namespace cache {

namespace detail {

namespace lnx {

uint64_t 
create_cache_config(const Event& evt) noexcept { // NOLINT
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

}

}

}

}
