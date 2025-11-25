#ifndef BENCHPP_PRIVATE_STATUSFILE_HPP
#define BENCHPP_PRIVATE_STATUSFILE_HPP

#include <fstream>
#include <string_view>

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

#endif /* BENCHPP_PRIVATE_STATUSFILE_HPP */
