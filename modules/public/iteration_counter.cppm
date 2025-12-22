module;

#include <cstddef>

export module Benchpp:iteration_counter;

namespace benchpp {

export
[[nodiscard]]
std::size_t
currentIteration(void) noexcept;

export
void
startIteration(const std::size_t num = 1); // dont call this twice ..

}

