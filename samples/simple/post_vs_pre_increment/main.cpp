#include <Bench++/timer.hpp>
#include <Bench++/stats.hpp>
#include <Bench++/macros.hpp>

#define RUN_NUM 100
#define LOOP_NUM 1e6

namespace benchpp {

namespace {

Timer M_postTimer;
Timer M_preTimer;

void
M_post_vs_pre_increment(void) {
  int a = 0;
  int b = 0;
  M_postTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    a = b++;
  }
  M_postTimer.recordAndReset();
  
  M_preTimer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    a = ++b;
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

BENCHMARK_MAIN(benchpp::M_post_vs_pre_increment(), RUN_NUM);
