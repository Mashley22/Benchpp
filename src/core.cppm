module;

#include <cstddef>

export module Benchpp;
export import :timer;
export import :cache;
export import :stats;

namespace benchpp {

[[nodiscard]]
std::size_t
currentIteration(void) noexcept;

void
startIteration(const std::size_t num = 1); // dont call this twice ..

}
