#ifndef BENCHPP_REGISTRY_HPP
#define BENCHPP_REGISTRY_HPP

#include <string_view>

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

void
run_benchmark(const std::string_view name);

void
run_benchmark(const std::string_view name, const std::size_t runNum);

void
run_group(const std::string_view groupName);

}

#endif /* BENCHPP_REGISTRY_HPP */
