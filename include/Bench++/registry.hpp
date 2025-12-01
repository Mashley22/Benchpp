#ifndef BENCHPP_REGISTRY_HPP
#define BENCHPP_REGISTRY_HPP

#include <string_view>

#define REGISTER_BENCHMARK(benchmark) \
bool benchmark##_registered_var = []() { \
  benchpp::add_benchmark(benchmark); \
  return true; \
} \

namespace benchpp {

struct BenchmarkNotRegisteredErr {
  BenchmarkNotRegisteredErr() = delete;
  BenchmarkNotRegisteredErr(const std::string_view) noexcept;
  std::string_view invalid_name;
};

struct BenchmarkInfo {
  std::string_view name;
  std::string_view group;
  void (*function)();
  std::size_t runNum{1};
};

void
add_benchmark(const BenchmarkInfo& info);

}

#endif /* BENCHPP_REGISTRY_HPP */
