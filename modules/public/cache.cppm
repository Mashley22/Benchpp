module;

#include <string>
#include <cstdint>

export module Benchpp:cache;

namespace benchpp {

namespace cache {

// NOT ALL OF THESE ARE ALWAYS AVAILABLE DEPENDING ON HARDWARE, AND KERNEL, WILL PROVIDE A TOOL FOR THIS I THINK,
// or just run the cache tests

export enum class Type { 
    L1D,    // L1 Data cache
    L1I,    // L1 Instruction cache  
    LL,     // Last Level Cache (L2/L3)
    DTLB,   // Data TLB
    ITLB,   // Instruction TLB
};

export enum class Operation {
    READ,      // Read operations
    WRITE,     // Write operations  
    PREFETCH   // Prefetch operations
};

export enum class Result {
    ACCESS,    // Total accesses
    MISS       // Misses only
};

export
[[nodiscard]]
std::string
type_toStr(const Type& type);

export
[[nodiscard]]
std::string
operation_toStr(const Operation& type);

export
[[nodiscard]]
std::string
result_toStr(const Result& type);


export struct Event {
  Type type;
  Operation op;
  Result res;
    
  [[nodiscard]]
  std::string 
  toStr(void) const;
};

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

export // NOLINT
template<Event T_evt>
class Counter : detail::Counter_impl {
public:
  Counter(void);

  ~Counter(void);
  
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
  using m_ = detail::Counter_impl;
};

}

}
