#ifndef BENCHPP_CACHE_HPP
#define BENCHPP_CACHE_HPP

#include <exception>

namespace benchpp {

namespace cache {

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
};

}

}

#ifdef __linux__
#ifndef BENCHPP_DETAIL_LINUX_HEADER // for the lsp
  #include "linux/cache.hpp" 
#endif
#else
#error "Only linux supported!"
#endif

#endif /* BENCHPP_CACHE_HPP */
