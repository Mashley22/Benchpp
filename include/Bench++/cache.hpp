#ifndef BENCHPP_CACHE_HPP
#define BENCHPP_CACHE_HPP

#include <string>

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

}

}

#ifdef __linux__
#ifndef BENCHPP_DETAIL_LINUX_HEADER // for the lsp
  #include "linux/cache.hpp" 
#endif
#endif

#endif /* BENCHPP_CACHE_HPP */
