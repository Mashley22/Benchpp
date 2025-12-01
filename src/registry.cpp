#include <Bench++/registry.hpp>
#include <Bench++/private/registry.hpp>

#include <iostream>

namespace benchpp {

BenchmarkNotRegisteredErr::BenchmarkNotRegisteredErr(const std::string_view val) noexcept {
  std::cerr << "No registered benchmark found with name: " << val << '\n';
  invalid_name = val;
}

void
register_benchmark(const BenchmarkInfo &info) {
  priv::register_benchmark(info);
}

}
