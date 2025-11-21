#include <Bench++/mem.hpp>
#include <Bench++/linux/mem.hpp>

#include "statusFile.hpp"

//TODO: self-adjust the readings?

namespace benchpp {

namespace mem {

[[nodiscard]]
std::size_t 
get_peakVirtual(void) {  //NOLINT
  return lnx::priv::parseStatusFile("VmPeak");
}

[[nodiscard]]
std::size_t
get_currentVirtual(void) {  //NOLINT
  return lnx::priv::parseStatusFile("VmSize");
}

[[nodiscard]]
std::size_t
get_peakPhysical(void) {  //NOLINT
  return lnx::priv::parseStatusFile("VmHWM");
}

[[nodiscard]]
std::size_t
get_currentPhysical(void) {  //NOLINT
  return lnx::priv::parseStatusFile("VmRSS");
}

[[nodiscard]]
std::size_t
get_currentSwapped(void) {  //NOLINT
  return lnx::priv::parseStatusFile("VmSwap");
}

[[nodiscard]]
std::optional<std::size_t>
try_get_peakVirtual(void) noexcept {  //NOLINT
  try {
    std::size_t res = lnx::priv::parseStatusFile("VmPeak");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]]
std::optional<std::size_t>
try_get_currentVirtual(void) noexcept {  //NOLINT
  try {
    std::size_t res = lnx::priv::parseStatusFile("VmSize");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]]
std::optional<std::size_t>
try_get_peakPhysical(void) noexcept {  //NOLINT
  try {
    std::size_t res = lnx::priv::parseStatusFile("VmHWM");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]]
std::optional<std::size_t>
try_get_currentPhysical(void) noexcept {  //NOLINT
  try {
    std::size_t res = lnx::priv::parseStatusFile("VmRSS");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]]
std::optional<std::size_t>
try_get_currentSwapped(void) noexcept {  //NOLINT
  try {
    std::size_t res = lnx::priv::parseStatusFile("VmSwap");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]]
Snapshot
get_snapshot(void) {  //NOLINT
  Snapshot snap = {
    .virt = get_currentVirtual(),
    .phy = get_currentPhysical(),
    .swap = get_currentSwapped()
  };

  return snap;
}

[[nodiscard]]
std::optional<Snapshot>
try_get_snapshot(void) noexcept {  //NOLINT
  try {
    Snapshot snap = get_snapshot();
    return snap;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

}

}
