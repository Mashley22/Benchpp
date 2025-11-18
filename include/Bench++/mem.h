#ifndef BENCHPP_MEM_HPP
#define BENCHPP_MEM_HPP

#include <cstddef>

namespace benchpp {

namespace mem {

// Note these may be non negligble, so it is recommned not to mix these with speed benchmarks
// May add more but keeping it simple for now

[[nodiscard]]
std::size_t
get_peakVirtual(void);

[[nodiscard]]
std::size_t
get_currentVirtual(void);

[[nodiscard]]
std::size_t
get_peakPhysical(void);

[[nodiscard]]
std::size_t
get_currentSwapped(void);

[[nodiscard]]
std::size_t
get_currentPhysical(void);

}

}

#endif /* BENCHPP_MEM_HPP */
