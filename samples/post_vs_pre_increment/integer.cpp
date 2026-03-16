#include <cstddef>
#include <iostream>

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

void
M_printStats(void) {
  if (!M_postTimer.times().empty()) {
    std::cout << "For the post increment: " << '\n';
    Stats<TimeCount_t>::generate(M_postTimer.times()).print();
  }
  if (!M_preTimer.times().empty()) {
    std::cout << "For the pre increment: " << '\n';
    Stats<TimeCount_t>::generate(M_preTimer.times()).print();
  }
}

char M_dummy = (std::atexit(M_printStats), 0);

}

}

namespace {

benchpp::BenchmarkInfo post = {
  .name = "post_increment",
  .group = "integer",
  .function = benchpp::M_post_increment,
  .runNum = RUN_NUM,
};

benchpp::BenchmarkInfo pre = {
  .name = "pre_increment",
  .group = "integer",
  .function = benchpp::M_pre_increment,
  .runNum = RUN_NUM,
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(pre);
