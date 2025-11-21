#ifndef BENCHPP_CACHE_HPP
#define BENCHPP_CACHE_HPP

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

}

}

#ifdef __linux__
#ifndef BENCHPP_DETAIL_LINUX_HEADER // for the lsp
  #include "detail/linux/core.hpp" 
#endif
#else
#error "Only linux supported!"
#endif

#endif /* BENCHPP_CACHE_HPP */
