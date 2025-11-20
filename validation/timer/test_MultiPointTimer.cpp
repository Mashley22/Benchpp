#include <Bench++/timer.hpp>

#include <catch2/catch_test_macros.hpp>

#define TIMER_RUN_COUNT 100
#define POINT_COUNT 3

namespace benchpp {

TEST_CASE( "Testing MultiPointTimer", "[Timer]") {
  
  MultiPointTimer<POINT_COUNT> timer;

  SECTION("MultiPointerTimer is empty") {
    REQUIRE(timer.times().size() == POINT_COUNT);
    for (const auto& point : timer.times()) {
      REQUIRE(point.empty());
    }
  }
  
  SECTION("MultiPointTimer many runs") {
    for (std::size_t i = 0; i < TIMER_RUN_COUNT; i++) {
      timer.start();

      for (std::size_t j = 0; j < POINT_COUNT; j++) {
        timer.lap();

        REQUIRE(timer.times()[j].size() == i + 1);
        REQUIRE(timer.times()[j][i] > Time_t{0}.count());
      }

      for (const auto& point : timer.times()) {
        REQUIRE(point.size() == i + 1);
      }

      timer.endRun();
    }
  }

}

}
