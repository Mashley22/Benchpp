#include <vector>
#include <iostream>
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
  .group = "iterator",
  .function = benchpp::M_post_increment,
  .runNum = RUN_NUM,
};

benchpp::BenchmarkInfo pre = {
  .name = "pre_increment",
  .group = "iterator",
  .function = benchpp::M_pre_increment,
  .runNum = RUN_NUM,
};

}

REGISTER_BENCHMARK(post);
REGISTER_BENCHMARK(pre);
