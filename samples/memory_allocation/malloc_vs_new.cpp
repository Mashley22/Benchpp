#include <cstddef>
#include <cstdlib>
#include <new>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 1000
#define ALLOCATION_COUNT std::size_t(100000)

namespace benchpp {
namespace {

Timer M_mallocTimer;
Timer M_newTimer;

BENCHPP_BENCHMARK_FUNC
void M_malloc_alloc() {
  M_mallocTimer.start();
  
  for (std::size_t i = 0; i < ALLOCATION_COUNT; i++) {
    void* ptr = std::malloc(sizeof(long) * 64);
    std::free(ptr);
  }
  
  M_mallocTimer.stop();
  M_mallocTimer.recordAndReset();
}

BENCHPP_BENCHMARK_FUNC
void M_new_alloc() {
  M_newTimer.start();
  
  for (std::size_t i = 0; i < ALLOCATION_COUNT; i++) {
    long* ptr = new long[64];
    delete[] ptr;
  }
  
  M_newTimer.stop();
  M_newTimer.recordAndReset();
}

}
}  

namespace {

benchpp::BenchmarkInfo malloc_bench{
  .name = "malloc/free",
  .group = "allocation",
  .function = benchpp::M_malloc_alloc,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_mallocTimer
};

benchpp::BenchmarkInfo new_bench{
  .name = "new/delete",
  .group = "allocation",
  .function = benchpp::M_new_alloc,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_newTimer
};

} 

REGISTER_BENCHMARK(malloc_bench);
REGISTER_BENCHMARK(new_bench);
