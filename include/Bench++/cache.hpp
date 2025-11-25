#ifndef BENCHPP_CACHE_HPP
#define BENCHPP_CACHE_HPP

#include <string>
#include <cstdint>

// TODO: make these macros more useful - tempting but not all combinations are actually always available
// expr is a macro that takes in Event as a parameter,
// this macro does expr over all event with specified type and operation
#define BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, operation) \
  expr(benchpp::cache::Event({type, operation, benchpp::cache::Result::ACCESS})); \
  expr(benchpp::cache::Event({type, operation, benchpp::cache::Result::MISS}));

// same as before but over all results and operations for a given type
#define BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, type) \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::READ); \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::WRITE); \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::PREFETCH);

// same as before but over all possible Event structs
#define BENCHPP_CACHE_EVENT_ALL_GENERATOR(expr) \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::L1D); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::L1I); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::LL); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::DTLB); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::ITLB); \

#define BENCHPP_CACHE_COUNTER_TEMPLATE_EXTERN_DECL(evt) extern template class Counter<evt>;

namespace benchpp {

namespace cache {

// NOT ALL OF THESE ARE ALWAYS AVAILABLE DEPENDING ON HARDWARE, AND KERNEL, WILL PROVIDE A TOOL FOR THIS I THINK,
// or just run the cache tests

enum class Type { 
    L1D,    // L1 Data cache
    L1I,    // L1 Instruction cache  
    LL,     // Last Level Cache (L2/L3)
    DTLB,   // Data TLB
    ITLB,   // Instruction TLB
};

enum class Operation {
    READ,      // Read operations
    WRITE,     // Write operations  
    PREFETCH   // Prefetch operations
};

enum class Result {
    ACCESS,    // Total accesses
    MISS       // Misses only
};

struct Event {
  Type type;
  Operation op;
  Result res;
  
  [[nodiscard]]
  std::string 
  toStr(void) const;
};

[[nodiscard]]
std::string
type_toStr(const Type& type);

[[nodiscard]]
std::string
operation_toStr(const Operation& type);

[[nodiscard]]
std::string
result_toStr(const Result& type);

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

BENCHPP_CACHE_EVENT_ALL_GENERATOR(BENCHPP_CACHE_COUNTER_TEMPLATE_EXTERN_DECL)

}

}

#endif /* BENCHPP_CACHE_HPP */
