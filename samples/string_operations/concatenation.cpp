#include <string>
#include <cstddef>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define LOOP_NUM std::size_t(1e5)

namespace benchpp {
namespace {

Timer M_concatAppendTimer;
Timer M_concatPlusTimer;
Timer M_concatReserveTimer;

/// Benchmark: String concatenation using +=
BENCHPP_BENCHMARK_FUNC
void M_concat_append() {
  M_concatAppendTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    std::string s = "Hello";
    s += " ";
    s += "World";
    (void)s;
  }
  M_concatAppendTimer.stop();
  M_concatAppendTimer.recordAndReset();
}

/// Benchmark: String concatenation using + operator (creates temporary)
BENCHPP_BENCHMARK_FUNC
void M_concat_plus() {
  M_concatPlusTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    std::string s = "Hello" + std::string(" ") + "World";
    (void)s;
  }
  M_concatPlusTimer.stop();
  M_concatPlusTimer.recordAndReset();
}

/// Benchmark: String concatenation with pre-allocated capacity
BENCHPP_BENCHMARK_FUNC
void M_concat_reserve() {
  M_concatReserveTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    std::string s;
    s.reserve(20);
    s += "Hello";
    s += " ";
    s += "World";
    (void)s;
  }
  M_concatReserveTimer.stop();
  M_concatReserveTimer.recordAndReset();
}

}  

}  

namespace {

benchpp::BenchmarkInfo append_bench{
  .name = "operator+=",
  .group = "concatenation",
  .function = benchpp::M_concat_append,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_concatAppendTimer
};

benchpp::BenchmarkInfo plus_bench{
  .name = "operator+",
  .group = "concatenation",
  .function = benchpp::M_concat_plus,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_concatPlusTimer
};

benchpp::BenchmarkInfo reserve_bench{
  .name = "with_reserve",
  .group = "concatenation",
  .function = benchpp::M_concat_reserve,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_concatReserveTimer
};

}

REGISTER_BENCHMARK(append_bench);
REGISTER_BENCHMARK(plus_bench);
REGISTER_BENCHMARK(reserve_bench);
