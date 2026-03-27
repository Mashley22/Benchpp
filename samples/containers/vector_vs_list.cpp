#include <vector>
#include <list>
#include <cstddef>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define ELEMENT_COUNT std::size_t(1e5)

namespace benchpp {
namespace {

Timer M_vectorIterTimer;
Timer M_listIterTimer;

BENCHPP_BENCHMARK_FUNC
void M_vector_sequential() {
  M_vectorIterTimer.start();
  
  std::vector<std::size_t> v;
  for (std::size_t i = 0; i < ELEMENT_COUNT; i++) {
    v.push_back(i);
  }
  
  volatile std::size_t sum = 0;
  for (std::size_t val : v) {
    sum += val;
  }
  
  M_vectorIterTimer.stop();
  M_vectorIterTimer.recordAndReset();
}

BENCHPP_BENCHMARK_FUNC
void M_list_sequential() {
  M_listIterTimer.start();
  
  std::list<std::size_t> lst;
  for (std::size_t i = 0; i < ELEMENT_COUNT; i++) {
    lst.push_back(i);
  }
  
  volatile std::size_t sum = 0;
  for (std::size_t val : lst) {
    sum += val;
  }
  
  M_listIterTimer.stop();
  M_listIterTimer.recordAndReset();
}

}

}

namespace {

benchpp::BenchmarkInfo vector_bench{
  .name = "vector",
  .group = "sequential write-read",
  .function = benchpp::M_vector_sequential,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_vectorIterTimer
};

benchpp::BenchmarkInfo list_bench{
  .name = "list",
  .group = "sequential write-read",
  .function = benchpp::M_list_sequential,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_listIterTimer
};

}

REGISTER_BENCHMARK(vector_bench);
REGISTER_BENCHMARK(list_bench);
