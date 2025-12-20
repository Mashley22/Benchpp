module;

#include <cstddef>
#include <optional>

export module Benchpp:mem;

export namespace benchpp {

namespace mem {

// Note these may be non negligble, so it is recommned not to mix these with speed benchmarks
// May add more but keeping it simple for now

/**@brief can be thrown by any of the getters if for some reasong they fail to get the memory
 */
class Error : std::exception {};

/**@brief contains the memory usage statistics at a particular point in time
 */
struct Snapshot {
  std::size_t virt;
  std::size_t phy;
  std::size_t swap;
};

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

[[nodiscard]]
Snapshot
get_snapshot(void);

[[nodiscard]]
std::optional<std::size_t>
try_get_peakVirtual(void) noexcept;

[[nodiscard]]
std::optional<std::size_t>
try_get_currentVirtual(void) noexcept;

[[nodiscard]]
std::optional<std::size_t>
try_get_peakPhysical(void) noexcept;

[[nodiscard]]
std::optional<std::size_t>
try_get_currentSwapped(void) noexcept;

[[nodiscard]]
std::optional<std::size_t>
try_get_currentPhysical(void) noexcept;

[[nodiscard]]
std::optional<Snapshot>
try_get_snapshot(void) noexcept;

}

}
