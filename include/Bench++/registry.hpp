#ifndef BENCHPP_REGISTRY_HPP
#define BENCHPP_REGISTRY_HPP

#include <string_view>
#include <sstream>

#define REGISTER_BENCHMARK(benchmark) \
static bool benchmark##_registered_var = []() { \
  benchpp::register_benchmark(benchmark); \
  return true; \
}()\

#define BENCHPP_BENCHMARK_GROUP_AND_NAME_STREAM(group_macro_val, name_macro_val)\
  group_macro_val << ":" << name_macro_val

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

#endif /* BENCHPP_REGISTRY_HPP */
