#ifndef BENCHPP_CACHE_HPP
#define BENCHPP_CACHE_HPP

#define BENCHPP_CACHE_TYPES_ALL \
  {benchpp::cache::Type::L1D, \
   benchpp::cache::Type::L1I, \
   benchpp::cache::Type::LL, \
   benchpp::cache::Type::DTLB, \
   benchpp::cache::Type::ITLB}

#define BENCHPP_CACHE_OPERATIONS_ALL \
  {benchpp::cache::Operation::READ, \
   benchpp::cache::Operation::WRITE, \
   benchpp::cache::Operation::PREFETCH}

#define BENCHPP_CACHE_RESULTS_ALL \
  {benchpp::cache::Result::ACCESS, \
   benchpp::cache::Result::ACCESS}

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
