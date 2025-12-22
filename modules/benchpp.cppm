module;

#include <cstddef>

export module Benchpp;
export import :stats;
export import :events;
export import :timer;
export import :cache;
export import :mem;
export import :lnx.exception.mem;
export import :core_metrics;

// import :priv.lnx.statusFile;
// g++ is having issues with this line, compiles fine on clang++ and g++ without this line
// so will leave it like that for now

namespace benchpp {

[[nodiscard]]
std::size_t
currentIteration(void) noexcept;

void
startIteration(const std::size_t num = 1); // dont call this twice ..

}
