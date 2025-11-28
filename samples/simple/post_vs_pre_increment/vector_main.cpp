#include <Bench++/timer.hpp>
#include <Bench++/stats.hpp>
#include <Bench++/macros.hpp>

#include <vector>

#define RUN_NUM 100
#define LOOP_NUM 1e6

namespace benchpp {

namespace {

Timer M_postTimer;
Timer M_preTimer;

std::vector<float> M_vec(LOOP_NUM);

void
M_post_vs_pre_increment_vector_iterators(void) {
  float a;
  M_postTimer.start();
  for (auto it = M_vec.begin(); it != M_vec.end(); it++) {
  }
  M_postTimer.recordAndReset();
  
  M_preTimer.start();
  for (auto it = M_vec.begin(); it != M_vec.end(); ++it) {
  }
  M_preTimer.recordAndReset();
  (void)a;
}

void
M_printStats(void) {
  std::cout << "For the post increment: " << '\n';
  Stats<TimeCount_t>::generate(M_postTimer.times()).print();
  std::cout << "For the pre increment: " << '\n';
  Stats<TimeCount_t>::generate(M_preTimer.times()).print();
}

int M_dummy = (std::atexit(M_printStats), 0);

}

}

BENCHMARK_MAIN(benchpp::M_post_vs_pre_increment_vector_iterators(), RUN_NUM);
