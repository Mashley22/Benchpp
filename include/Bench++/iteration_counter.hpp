#ifndef BENCHPP_ITERATION_COUNTER_HPP
#define BENCHPP_ITERATION_COUNTER_HPP

#include <cstddef>

namespace benchpp {

[[nodiscard]]
std::size_t
currentIteration(void) noexcept;

void
startIteration(const std::size_t num = 0); // dont call this twice ..

}

#endif /* BENCHPP_ITERATION_COUNTER_HPP */
