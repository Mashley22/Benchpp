module;

#include <string_view>
#include <sstream>

export module Benchpp:registry;

namespace benchpp {

struct BenchmarkNotRegisteredErr {
  BenchmarkNotRegisteredErr() = delete;
  BenchmarkNotRegisteredErr(const std::string_view groupName_val, const std::string_view name_val) noexcept;
  std::string_view name;
  std::string_view groupName;
};

struct BenchmarkInfo {
  std::string_view name;
  std::string_view group;
  void (*function)();
  std::size_t runNum{1};

  [[nodiscard]]
  std::stringstream
  id_to_sstream(void) const;
};

void
register_benchmark(const BenchmarkInfo& info);

}
