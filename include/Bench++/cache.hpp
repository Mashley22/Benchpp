#ifndef BENCHPP_PERF_HPP
#define BENCHPP_PERF_HPP


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

#endif /* BENCHPP_PERF_HPP */
