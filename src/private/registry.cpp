#include <Bench++/private/registry.hpp>

#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <iostream>

#define GROUP_RUNNER_INVALID_IDX std::numeric_limits<std::size_t>::max()

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

void
M_run_benchmark_impl(const BenchmarkInfo& benchmark, const std::size_t runNum) {
  std::cout << "Starting benchmark: " << benchmark.name
            <<  " for " << runNum << " runs" << '\n';

  for (std::size_t i = 0; i < runNum; i++) {
    std::cout << "Run: " << runNum << '\n';
    benchmark.function();
  }

  std::cout << "Finished benchmark: " << benchmark.name
            <<  " did " << runNum << " runs" << '\n';
}

}

void
add_benchmark(const BenchmarkInfo &info) {
  M_registeredBenchmarks.push_back(info);
}

void
run_benchmark(const BenchmarkInfo& benchmark, const std::size_t runNum) {
  M_run_benchmark_impl(benchmark, runNum);
}

void
run_benchmark(const BenchmarkInfo& benchmark) {
  M_run_benchmark_impl(benchmark, benchmark.runNum);
}

void
run_benchmark(const std::string_view name) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(name);
  
  M_run_benchmark_impl(*it, it->runNum);
}

void
run_benchmark(const std::string_view name, const std::size_t runNum) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(name);
  
  M_run_benchmark_impl(*it, runNum);
}

GroupRunner::GroupRunner(const std::string_view groupName) noexcept :
  m_name(groupName) {}

bool
GroupRunner::nextBenchmark(void) noexcept {
  assert(m_currentIdx != GROUP_RUNNER_INVALID_IDX);
  
  if (m_currentIdx != 0) {
    m_currentIdx++;
  }
  
  while (m_currentIdx < M_registeredBenchmarks.size()) {
    if (M_registeredBenchmarks[m_currentIdx].name == m_name) {
      return true;
    }
    m_currentIdx++;
  }
  
  m_currentIdx = GROUP_RUNNER_INVALID_IDX;
  return false;
}

const BenchmarkInfo&
GroupRunner::currentBenchmark(void) const noexcept {
  assert(m_currentIdx != GROUP_RUNNER_INVALID_IDX);
  
  return M_registeredBenchmarks[m_currentIdx];
}

void
GroupRunner::reset(void) noexcept {
  m_currentIdx = 0;
}

}

}
