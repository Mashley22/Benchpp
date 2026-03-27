#include <vector>
#include <algorithm>
#include <random>
#include <cstddef>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 1000
#define ELEMENT_COUNT std::size_t(1e5)

namespace benchpp {
namespace {

Timer M_stdSortTimer;
Timer M_stdStableSortTimer;
Timer M_stdPartialSortTimer;

std::vector<int> M_generate_random_data() {
  std::vector<int> data(ELEMENT_COUNT);
  std::mt19937 gen(42);
  std::uniform_int_distribution<> dis(1, 1000000);
  for (auto& val : data) {
    val = dis(gen);
  }
  return data;
}

/// Benchmark: std::sort (quicksort-based, not stable)
BENCHPP_BENCHMARK_FUNC
void M_std_sort() {
  auto data = M_generate_random_data();

  M_stdSortTimer.start();
  std::sort(data.begin(), data.end());
  
  M_stdSortTimer.stop();
  M_stdSortTimer.recordAndReset();
}

/// Benchmark: std::stable_sort (mergesort-based, stable)
BENCHPP_BENCHMARK_FUNC
void M_std_stable_sort() {
  auto data = M_generate_random_data();

  M_stdStableSortTimer.start();
  std::stable_sort(data.begin(), data.end());
  
  M_stdStableSortTimer.stop();
  M_stdStableSortTimer.recordAndReset();
}

/// Benchmark: std::partial_sort (finds N smallest, partial heap sort)
BENCHPP_BENCHMARK_FUNC
void M_std_partial_sort() {
  auto data = M_generate_random_data();
  
  M_stdPartialSortTimer.start();
  std::partial_sort(data.begin(), data.begin() + 100, data.end());
  
  M_stdPartialSortTimer.stop();
  M_stdPartialSortTimer.recordAndReset();
}

}  
}  

namespace {

benchpp::BenchmarkInfo sort_bench{
  .name = "sort",
  .group = "algorithms",
  .function = benchpp::M_std_sort,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_stdSortTimer
};

benchpp::BenchmarkInfo stable_sort_bench{
  .name = "stable_sort",
  .group = "algorithms",
  .function = benchpp::M_std_stable_sort,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_stdStableSortTimer
};

benchpp::BenchmarkInfo partial_sort_bench{
  .name = "partial_sort",
  .group = "algorithms",
  .function = benchpp::M_std_partial_sort,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_stdPartialSortTimer
};

} 

REGISTER_BENCHMARK(sort_bench);
REGISTER_BENCHMARK(stable_sort_bench);
REGISTER_BENCHMARK(partial_sort_bench);
