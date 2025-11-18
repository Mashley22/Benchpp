#include <Bench++/stats.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstdint>

namespace benchpp {

TEST_CASE( "range works for basic numeric types", "[stats]") {

  SECTION( "int8" ) {
    std::uint8_t max, min;
    max = 100;
    min = 50;

    Stats<std::uint8_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

}

}
