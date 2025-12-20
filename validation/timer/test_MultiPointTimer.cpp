#include <catch2/catch_test_macros.hpp>

import Benchpp;

#define TIMER_RUN_COUNT 100
#define POINT_COUNT 3

namespace benchpp {

TEST_CASE( "Testing MultiPointTimer", "[Timer]") {
  
  MultiPointTimer<POINT_COUNT, TIMER_RUN_COUNT> timer;

  for (std::size_t i = 0; i < TIMER_RUN_COUNT; i++) {
    timer.start();

    for (std::size_t j = 0; j < POINT_COUNT; j++) {
      timer.lap();

    }

    timer.run_complete();
  }

  SECTION("MultiPointTimer::get_run()") {
    for (std::size_t i = 0; i < TIMER_RUN_COUNT; i++) {
      for (std::size_t j = 0; j < POINT_COUNT; j++) {
        REQUIRE(timer.get_run(i).size() == POINT_COUNT);
        REQUIRE(timer.get_run(i)[j] > 0);
        REQUIRE(timer.get_run(i)[j] != TimeCount_t{}); // not sure about these
      }
    }
  }

  SECTION("MultiPointTimer::get_point()") {
    for (std::size_t i = 0; i < POINT_COUNT; i++) {
      for (std::size_t j = 0; j < TIMER_RUN_COUNT; j++) {
        auto val = timer.get_point(i);
        REQUIRE(val.size() == TIMER_RUN_COUNT);
        REQUIRE(val[j] > 0);
        REQUIRE(val[j] != TimeCount_t{});
      }
    }
  }

}

}
