module;

#include <fstream>
#include <string_view>

export module Benchpp:priv.lnx.statusFile;

namespace benchpp {

namespace priv { 

namespace lnx {

[[nodiscard]]
std::ifstream
openStatusFile(void);

[[nodiscard]]
std::size_t
parseStatusFile(const std::string_view key);

}

}

}
