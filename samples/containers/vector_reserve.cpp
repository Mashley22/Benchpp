#include <vector>
#include <cstddef>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define ELEMENT_COUNT std::size_t(1e5)

namespace benchpp {
namespace {

Timer M_vectorNoReserveTimer;
Timer M_vectorReserveTimer;

BENCHPP_BENCHMARK_FUNC
void M_vector_no_reserve() {
  M_vectorNoReserveTimer.start();
  
  [[maybe_unused]] std::vector<std::size_t> v;
  for (std::size_t i = 0; i < ELEMENT_COUNT; i++) {
    v.push_back(i);
  }
  
  M_vectorNoReserveTimer.stop();
  M_vectorNoReserveTimer.recordAndReset();
}

BENCHPP_BENCHMARK_FUNC
void M_vector_with_reserve() {
  M_vectorReserveTimer.start();
  
  [[maybe_unused]] std::vector<std::size_t> v;
  v.reserve(ELEMENT_COUNT);  
  for (std::size_t i = 0; i < ELEMENT_COUNT; i++) {
    v.push_back(i);
  }
  
  M_vectorReserveTimer.stop();
  M_vectorReserveTimer.recordAndReset();
}

}

}

namespace {

benchpp::BenchmarkInfo no_reserve_bench{
  .name = "no_reserve",
  .group = "vector_allocation",
  .function = benchpp::M_vector_no_reserve,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_vectorNoReserveTimer
};

benchpp::BenchmarkInfo reserve_bench{
  .name = "with_reserve",
  .group = "vector_allocation",
  .function = benchpp::M_vector_with_reserve,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_vectorReserveTimer
};

}

REGISTER_BENCHMARK(no_reserve_bench);
REGISTER_BENCHMARK(reserve_bench);
