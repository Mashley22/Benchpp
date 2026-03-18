#include <cstddef>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 1000
#define LOOP_NUM std::size_t(1e6)

namespace benchpp {

namespace {

Timer M_postTimer;
Timer M_preTimer;

BENCHPP_BENCHMARK_FUNC
void
M_post_increment(void) {
  M_postTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    LOOP_FODDER;
  }
  M_postTimer.stop();
  M_postTimer.recordAndReset();
}

BENCHPP_BENCHMARK_FUNC
void
M_pre_increment(void) {
  M_preTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; ++i) {
    LOOP_FODDER;
  }
  M_preTimer.stop();
  M_preTimer.recordAndReset();
}

}

}

namespace {

benchpp::BenchmarkInfo post = {
  .name = "post_increment",
  .group = "integer",
  .function = benchpp::M_post_increment,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_postTimer
};

benchpp::BenchmarkInfo pre = {
  .name = "pre_increment",
  .group = "integer",
  .function = benchpp::M_pre_increment,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_preTimer
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(pre);
