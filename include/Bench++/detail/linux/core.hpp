#ifndef BENCHPP_DETAIL_LINUX_CORE_HPP
#define BENCHPP_DETAIL_LINUX_CORE_HPP

#ifndef BENCHPP_DETAIL_LINUX_HEADER
#define BENCHPP_DETAIL_LINUX_HEADER
#endif

#include <Bench++/cache.hpp>

#include <linux/perf_event.h>

#include <cstdint>

namespace benchpp {

namespace cache {

namespace detail {

namespace lnx {

template<Type T_cache,
         Operation T_op,
         Result T_result>
[[nodiscard]]
uint64_t 
create_cache_config(void) noexcept {  //NOLINT
    uint64_t cache_val, op_val, result_val;
    
    switch (T_cache) {
        case Type::L1D:  cache_val = PERF_COUNT_HW_CACHE_L1D; break;
        case Type::L1I:  cache_val = PERF_COUNT_HW_CACHE_L1I; break;
        case Type::LL:   cache_val = PERF_COUNT_HW_CACHE_LL; break;
        case Type::DTLB: cache_val = PERF_COUNT_HW_CACHE_DTLB; break;
        case Type::ITLB: cache_val = PERF_COUNT_HW_CACHE_ITLB; break;
        default:              cache_val = PERF_COUNT_HW_CACHE_L1D; break;
    }
    
    switch (T_op) {
        case Operation::READ:     op_val = PERF_COUNT_HW_CACHE_OP_READ; break;
        case Operation::WRITE:    op_val = PERF_COUNT_HW_CACHE_OP_WRITE; break;
        case Operation::PREFETCH: op_val = PERF_COUNT_HW_CACHE_OP_PREFETCH; break;
        default:                       op_val = PERF_COUNT_HW_CACHE_OP_READ; break;
    }
    
    switch (T_result) {
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


#endif /* BENCHPP_DETAIL_LINUX_CORE_HPP */
