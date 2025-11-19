#include <Bench++/timer.hpp>

#include <catch2/catch_test_macros.hpp>


namespace benchpp {

TEST_CASE( "BasicTimer", "[Timer]") {
  
  SECTION( "Default 0 time" ) {
    
    BasicTimer timer;
    REQUIRE(timer.duration() == Time_t{0});

  }

}

}
