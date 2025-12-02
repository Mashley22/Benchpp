#include <Bench++/registry.hpp>
#include <Bench++/private/registry.hpp>

#include <iostream>

namespace benchpp {

BenchmarkNotRegisteredErr::BenchmarkNotRegisteredErr(const std::string_view groupName_val, const std::string_view name_val) noexcept {
  std::cerr << "No registered benchmark found with name: " << BENCHPP_BENCHMARK_GROUP_AND_NAME_STREAM(groupName_val, name_val) << '\n';
  groupName = groupName_val;
  name = name_val;
}

void
register_benchmark(const BenchmarkInfo &info) {
  priv::register_benchmark(info);
}

}
