#include <Bench++/private/registry.hpp>

#include <vector>
#include <algorithm>

namespace benchpp {

namespace priv {

namespace {

std::vector<BenchmarkInfo> M_registeredBenchmarks;

std::vector<BenchmarkInfo>::const_iterator
M_findBenchmark(const std::string_view name) {
  std::vector<BenchmarkInfo>::const_iterator it = 
    std::find_if(M_registeredBenchmarks.begin(),
                 M_registeredBenchmarks.end(),
                 [&name](const BenchmarkInfo& info) {
                   return info.name == name;
                 });

  if (it == M_registeredBenchmarks.end()) {
    throw BenchmarkNotRegisteredErr(name);
  }

  return it;
}

}

void
add_benchmark(const BenchmarkInfo &info) {
  M_registeredBenchmarks.push_back(info);
}

void
run_benchmark(const BenchmarkInfo& benchmark, const std::size_t runNum) {
  for (std::size_t i = 0; i < runNum; i++) {
    benchmark.function();
  }
}

void
run_benchmark(const BenchmarkInfo& benchmark) {
  run_benchmark(benchmark, benchmark.runNum);
}

void
run_benchmark(const std::string_view name) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(name);
  
  run_benchmark(*it);
}

void
run_benchmark(const std::string_view name, const std::size_t runNum) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(name);
  
  run_benchmark(*it, runNum);
}

}

}
