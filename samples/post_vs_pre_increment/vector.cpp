#include <vector>
#include <cstdlib>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define LOOP_NUM 1e7

namespace benchpp {

namespace {

Timer M_postTimer;
Timer M_preTimer;

std::vector<float> M_vec(LOOP_NUM);

BENCHPP_BENCHMARK_FUNC
void
M_post_increment(void) {
  M_postTimer.start();
  for (auto it = M_vec.begin(); it != M_vec.end(); it++) {
    LOOP_FODDER;
  }
  M_postTimer.stop();
  M_postTimer.recordAndReset();
}

BENCHPP_BENCHMARK_FUNC
void
M_pre_increment(void) {
  M_preTimer.start();
  for (auto it = M_vec.begin(); it != M_vec.end(); ++it) {
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
  .group = "iterator",
  .function = benchpp::M_post_increment,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_postTimer
};

benchpp::BenchmarkInfo pre = {
  .name = "pre_increment",
  .group = "iterator",
  .function = benchpp::M_pre_increment,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_preTimer
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(pre);
