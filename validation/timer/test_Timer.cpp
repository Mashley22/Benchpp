#include <Bench++/timer.hpp>

#include <catch2/catch_test_macros.hpp>

#define TIMER_START_STOP_COUNT 100

namespace benchpp {

TEST_CASE( "Timer", "[Timer]" ) {
  
  Timer timer;

  SECTION( "Timer is empty by default" ) {
    REQUIRE(timer.times().empty());
  }

  SECTION( "Timer a single start stop sequence correctly (multiple times)" ) {
    for (std::size_t i = 0; i < TIMER_START_STOP_COUNT; i++) {
      timer.start();
      timer.stop();
      Time_t time = timer.duration();
      timer.record();

      REQUIRE(timer.times().size() == i + 1);
      REQUIRE(time.count() == timer.times()[i]);
    }
  }

  SECTION( "Timer records without stopping are sequential, i.e stop doesn't reset" ) {
    timer.start();
    timer.record();
    for (std::size_t i = 0; i < TIMER_START_STOP_COUNT; i++) {
      timer.record();

      REQUIRE(timer.times().size() == i + 2);
      REQUIRE(timer.times()[i] < timer.times()[i + 1]);
    }
  }

  SECTION( "Timer record and reset works properly (i.e like record reset)" ) {
    for (std::size_t i = 0; i < TIMER_START_STOP_COUNT; i++) {
      timer.start();
      timer.recordAndReset();

      REQUIRE(timer.times().size() == i + 1);
      REQUIRE(timer.times()[i] > 0);
    }
    
  }

}

}
