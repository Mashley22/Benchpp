#include <cstddef>
#include <atomic>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define LOOP_NUM std::size_t(1e6)

namespace benchpp {

namespace {

Timer M_atomicIncrementTimer;
Timer M_incrementTimer;

BENCHPP_BENCHMARK_FUNC
void
M_atomicIncrement(void) {
  std::atomic<char*> pointer{};
  M_atomicIncrementTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    pointer++;
  }
  M_atomicIncrementTimer.stop();
  M_atomicIncrementTimer.recordAndReset();
  (void)pointer;
}

BENCHPP_BENCHMARK_FUNC
void
M_increment(void) {
  char* pointer{};
  M_incrementTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    pointer++;
  }
  M_incrementTimer.stop();
  M_incrementTimer.recordAndReset();
  (void)pointer;
}

}

}

namespace {

benchpp::BenchmarkInfo post = {
  .name = "atomic",
  .group = "increment",
  .function = benchpp::M_atomicIncrement,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_atomicIncrementTimer
};

benchpp::BenchmarkInfo increment = {
  .name = "normal",
  .group = "increment",
  .function = benchpp::M_increment,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_incrementTimer
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(increment);
