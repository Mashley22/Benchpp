#include <fstream>
#include <string_view>

namespace benchpp {

namespace mem {

namespace lnx {

namespace priv {

[[nodiscard]]
std::ifstream
openStatusFile(void);

[[nodiscard]]
std::size_t
parseStatusFile(const std::string_view key);

}

}

}

}
