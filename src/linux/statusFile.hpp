#include <Bench++/linux/exception/mem.hpp>

#include <fstream>
#include <string_view>
#include <string>

#define LINUX_STATUS_FILE "/proc/self/status"

namespace benchpp {

namespace mem {

namespace lnx {

namespace priv {

[[nodiscard]] inline
std::ifstream
openStatusFile(void) {
  std::ifstream statusFile;
  statusFile.open(LINUX_STATUS_FILE);

  if (!statusFile.is_open()) {
    throw OpenStatusFileErr();
  }

  return statusFile;
}

[[nodiscard]] inline
std::size_t
parseStatusFile(const std::string_view key) {
  std::ifstream statusFile = openStatusFile();
  std::string line;

  while(std::getline(statusFile, line)) {
    if (line.find(key) == 0) {
      std::size_t num_start = line.find_first_of("0123456789", key.length()); // start after the length of the key

      if (num_start == std::string::npos) {
        throw LineParseErr();
      }
      
      std::size_t num_end = line.find(' ', num_start); // space for the stuff

      if (num_end == std::string::npos) {
        throw LineParseErr();
      }
    
      std::string num_str = line.substr(num_start, num_end);
      std::size_t retval;
      try {
        retval = std::stoull(num_str);
      }
      catch(std::exception& e) {
        throw StrTo_ull_Err();
      }
        
      return retval;
    }
  }
  
  throw KeyNotFoundErr();
}

}

}

}

}
