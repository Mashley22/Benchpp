module;

#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <iostream>

module Benchpp;
import :priv.registry;

#define GROUP_RUNNER_INVALID_IDX std::numeric_limits<std::size_t>::max()
#define GROUP_RUNNER_START_IDX GROUP_RUNNER_INVALID_IDX - 1 // no ones using this surely

namespace benchpp {

namespace priv {

namespace {

[[nodiscard]]
std::vector<BenchmarkInfo>& 
M_registeredBenchmarks(void) noexcept {
  static std::vector<BenchmarkInfo> s_registeredBenchmarks = {}; // this shouldn't be needed on deinitialization?

  return s_registeredBenchmarks;
}

std::vector<BenchmarkInfo>::const_iterator
M_findBenchmark(const std::string_view groupName, const std::string_view name) {
  std::cout << groupName << '\n'; 
  std::cout << name << std::endl;
  std::vector<BenchmarkInfo>::const_iterator it = 
    std::find_if(M_registeredBenchmarks().begin(),
                 M_registeredBenchmarks().end(),
                 [&name, &groupName](const BenchmarkInfo& info) {
                   return (info.name == name) && (info.group == groupName);
                 });

  if (it == M_registeredBenchmarks().end()) {
    throw BenchmarkNotRegisteredErr(groupName, name);
  }

  return it;
}

void
M_run_benchmark_impl(const BenchmarkInfo& benchmark, const std::size_t runNum) {
  std::cout << "Starting benchmark: " << benchmark.id_to_sstream().rdbuf()
            << " for: " << runNum << " runs" << '\n';


  for (std::size_t i = 1; i <= runNum; i++) {
    std::cout << "Run: " << i << '\n';
    benchmark.function();
  }

  std::cout << "Finished benchmark: " << benchmark.id_to_sstream().rdbuf()
            << " for: " << runNum << " runs" << '\n';
}

void
M_print_benchmarkInfo(const BenchmarkInfo& benchmark) {
  std::cout << benchmark.group << ":" << benchmark.name << "   runs:" << benchmark.runNum << '\n';
}

[[nodiscard]]
std::vector<std::string_view>
M_find_all_groups(void) {
  std::vector<std::string_view> groups;
  
  for (const BenchmarkInfo& info : M_registeredBenchmarks()) {
    if (std::find(groups.begin(), groups.end(), info.group) == groups.end()) {
      groups.push_back(info.group);
    }
  }

  return groups;
}

[[nodiscard]]
std::size_t
M_num_benchmarks_in_group(const std::string_view groupName) noexcept {
  std::size_t retval = 0;
  GroupRunner runner(groupName);

  while (runner.nextBenchmark()) {
    retval++;
  }

  return retval;
}

}

void
register_benchmark(const BenchmarkInfo &info) {
  M_registeredBenchmarks().push_back(info);
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
run_benchmark(const std::string_view groupName, const std::string_view name) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(groupName, name);
  
  M_run_benchmark_impl(*it, it->runNum);
}

void
run_benchmark(const std::string_view groupName, const std::string_view name, const std::size_t runNum) {
  std::vector<BenchmarkInfo>::const_iterator it = M_findBenchmark(groupName, name);
  
  M_run_benchmark_impl(*it, runNum);
}

void
run_group(const std::string_view name) {
  GroupRunner runner(name);
  std::cout << "Starting group: " << name << '\n';

  while(runner.nextBenchmark()) {
    run_benchmark(runner.currentBenchmark());
  }

  std::cout << "Finished group: " << name << '\n';
}

void 
run_all(void) {
  std::cout << "Running all benchmarks" << '\n';
  for (const auto& benchmark : M_registeredBenchmarks()) {
    run_benchmark(benchmark);
  }
}

void
print_all_benchmarks(void) {
  for (const BenchmarkInfo& info : M_registeredBenchmarks()) {
    M_print_benchmarkInfo(info);
  }
}

void
print_all_groups(void) {
  auto groups = M_find_all_groups();

  std::cout << "Found " << groups.size() << " groups" << '\n';

  for (const auto& name : groups) {
    std::cout << name << '\n';
  }
}

void
print_all_benchmarks_in_group(const std::string_view groupName) {
  std::cout << M_num_benchmarks_in_group(groupName) << " benchmarks in group: " << groupName << '\n';

  GroupRunner runner(groupName);

  while (runner.nextBenchmark()) {
    std::cout << runner.currentBenchmark().name << '\n';
  }
}

GroupRunner::GroupRunner(const std::string_view groupName) noexcept :
  m_name(groupName), m_currentIdx(GROUP_RUNNER_START_IDX) {}

bool
GroupRunner::nextBenchmark(void) noexcept {
  assert(m_currentIdx != GROUP_RUNNER_INVALID_IDX);
  
  if (m_currentIdx != GROUP_RUNNER_START_IDX) {
    m_currentIdx++;
  }
  else {
    m_currentIdx = 0;
  }

  while (m_currentIdx < M_registeredBenchmarks().size()) {
    if (M_registeredBenchmarks()[m_currentIdx].group == m_name) {
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
  
  return M_registeredBenchmarks()[m_currentIdx];
}

void
GroupRunner::reset(void) noexcept {
  m_currentIdx = GROUP_RUNNER_START_IDX;
}

}

}
