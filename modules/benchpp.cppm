module;

#include <cstddef>

export module Benchpp;
export import :stats;
export import :events;
export import :timer;
export import :cache;

namespace benchpp {

[[nodiscard]]
std::size_t
currentIteration(void) noexcept;

void
startIteration(const std::size_t num = 1); // dont call this twice ..

}
