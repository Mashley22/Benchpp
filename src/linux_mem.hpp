#include <Bench++/mem.hpp>
#include <Bench++/linux/mem.hpp>

#include <fstream>
#include <string_view>
#include <string>

#define LINUX_STATUS_FILE "/proc/status/status"

//TODO: self-adjust the readings?

namespace benchpp {

namespace mem {

namespace {

[[nodiscard]]
std::ifstream
M_openStatusFile(void) {
  std::ifstream statusFile;
  statusFile.open(LINUX_STATUS_FILE);

  if (!statusFile.is_open()) {
    throw lnx::OpenStatusFileErr();
  }

  return statusFile;
}

[[nodiscard]]
std::size_t
M_parseStatusFile(const std::string_view key) {
  std::ifstream statusFile = M_openStatusFile();

  std::string line;

  while(std::getline(statusFile, line)) {
    if (line.find(key) == 0) {
      std::size_t num_start = line.find_first_of("0123456789", key.length()); // start after the length of the key

      if (num_start == std::string::npos) {
        throw lnx::LineParseError();
      }
      
      std::size_t num_end = line.find(' ', num_start); // space for the stuff

      if (num_end == std::string::npos) {
        throw lnx::LineParseError();
      }
    
      std::string num_str = line.substr(num_start, num_end);
      std::size_t retval;
      try {
        retval = std::stoull(num_str);
      }
      catch(std::exception& e) {
        throw lnx::StrTo_ull_Error();
      }
        
      return retval;
    }
  }
  
  throw lnx::KeyNotFoundError();
}

}

[[nodiscard]] inline
std::size_t 
get_peakVirtual(void) {
  return M_parseStatusFile("VmPeak");
}

[[nodiscard]] inline
std::size_t
get_currentVirtual(void) {
  return M_parseStatusFile("VmSize");
}

[[nodiscard]] inline
std::size_t
get_peakPhysical(void) {
  return M_parseStatusFile("VmHWM");
}

[[nodiscard]] inline
std::size_t
get_currentPhysical(void) {
  return M_parseStatusFile("VmRSS");
}

[[nodiscard]] inline
std::optional<std::size_t>
try_get_peakVirtual(void) noexcept {
  try {
    std::size_t res = M_parseStatusFile("VmPeak");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]] inline
std::optional<std::size_t>
try_get_currentVirtual(void) noexcept {
  try {
    std::size_t res = M_parseStatusFile("VmSize");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]] inline
std::optional<std::size_t>
try_get_peakPhysical(void) noexcept {
  try {
    std::size_t res = M_parseStatusFile("VmHWM");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]] inline
std::optional<std::size_t>
try_get_currentPhysical(void) noexcept {
  try {
    std::size_t res = M_parseStatusFile("VmRSS");
    return res;
  }
  catch(Error& e) {
    return std::nullopt;
  }
}

[[nodiscard]] inline
Snapshot
get_snapshot(void) {
  Snapshot snap = {
    .virt = get_currentVirtual(),
    .phy = get_currentPhysical(),
    .swap = get_currentSwapped()
  };

  return snap;
}

[[nodiscard]] inline
std::optional<Snapshot>
try_get_snapshot(void) noexcept {
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
