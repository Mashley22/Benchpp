#include <cstddef>
#include <iostream>
#include <atomic>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define LOOP_NUM std::size_t(1e6)

namespace benchpp {

namespace {

Timer M_atomicloadTimer;
Timer M_loadTimer;

BENCHPP_BENCHMARK_FUNC
void
M_atomicload(void) {
  std::atomic<char*> pointer{};
  M_atomicloadTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    volatile auto val = pointer.load(std::memory_order_relaxed);
    (void)val;
  }
  M_atomicloadTimer.stop();
  M_atomicloadTimer.recordAndReset();
  (void)pointer;
}

BENCHPP_BENCHMARK_FUNC
void
M_load(void) {
  char* pointer{};
  M_loadTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    volatile auto val = pointer;
    (void)val;
  }
  M_loadTimer.stop();
  M_loadTimer.recordAndReset();
  (void)pointer;
}

}

}

namespace {

benchpp::BenchmarkInfo post = {
  .name = "atomic",
  .group = "load",
  .function = benchpp::M_atomicload,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_atomicloadTimer
};

benchpp::BenchmarkInfo load = {
  .name = "normal",
  .group = "load",
  .function = benchpp::M_load,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_loadTimer
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(load);
