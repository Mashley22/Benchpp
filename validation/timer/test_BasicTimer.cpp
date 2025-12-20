#include <catch2/catch_test_macros.hpp>

import Benchpp;

#define START_STOP_CYCLE_COUNT 100

namespace benchpp {

namespace {

void M_smallStall(void) noexcept {
  int x = 0;
  x++;
  x++;

  REQUIRE(x == 2);
}

}

TEST_CASE( "BasicTimer", "[Timer]") {
  
  BasicTimer timer;

  SECTION( "Default 0 time" ) {
    
    REQUIRE(timer.duration() == Time_t{0});

  }

  SECTION( "start" ) {
    
    timer.start();

    REQUIRE(timer.duration() >= Time_t{0});
  }

  SECTION( "stop, duration doesn't change after stopping" ) {

    timer.start();

    timer.stop();

    REQUIRE(timer.duration() > Time_t{0});
    
    Time_t time = timer.duration();

    M_smallStall();

    REQUIRE(timer.duration() == time);
  }

  SECTION( "repeated stop starts only increase the time" ) {

    for (std::size_t i = 0; i < START_STOP_CYCLE_COUNT; i++) {
      Time_t timeAccumulate{timer.duration()};

      timer.start();
      M_smallStall();
      timer.stop();
    
      REQUIRE(timer.duration() > timeAccumulate);
    }

  }

  SECTION( "reset" ) {

    timer.start();
    M_smallStall();
    timer.stop();
    
    timer.reset();
    
    REQUIRE(timer.duration() == Time_t{0});

    timer.start();
    M_smallStall();
    timer.stop();
    timer.reset();

    REQUIRE(timer.duration() == Time_t{0});
  }

}

}
