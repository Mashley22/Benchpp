#include <Bench++/stats.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>

namespace benchpp {

// A bit overkill... rest will just use std::(u)int64_t and double

TEST_CASE( "range works for basic unsigned integer types", "[stats]") {

  SECTION( "uint8_t" ) {
    std::uint8_t max, min;
    max = 100;
    min = 50;

    Stats<std::uint8_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "uint16_t" ) {
    std::uint16_t max, min;
    max = 9086;
    min = 42;

    Stats<std::uint16_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "uint32_t" ) {
    std::uint32_t max, min;
    max = 910283;
    min = 10283;

    Stats<std::uint32_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "uint64_t" ) {
    std::uint64_t max, min;
    max = 1000000000;
    min = 5000;

    Stats<std::uint64_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

}

TEST_CASE( "range works for basic signed integer types", "[stats]") {

  SECTION( "int8_t" ) {
    std::int8_t max, min;
    max = 100;
    min = 50;

    Stats<std::int8_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "int16_t" ) {
    std::int16_t max, min;
    max = 9086;
    min = 42;

    Stats<std::int16_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "int32_t" ) {
    std::int32_t max, min;
    max = 910283;
    min = 10283;

    Stats<std::int32_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

  SECTION( "int64_t" ) {
    std::int64_t max, min;
    max = 1000000000;
    min = 5000;

    Stats<std::int64_t> stats;
    stats.max = max;
    stats.min = min;

    REQUIRE(stats.range() == max - min);
  }

}

namespace {

template<typename T>
void test_range_floating_point(T max, T min) noexcept {
  Stats<T> stats;
  stats.max = max;
  stats.min = min;

  REQUIRE_THAT(stats.range(), Catch::Matchers::WithinRel(max - min));
}

}

TEST_CASE( "ranges works for floats", "[stats]") {

  test_range_floating_point<float>(0.001f, 0.00f);
  test_range_floating_point<float>(10000.0f, 9.0089f);
  test_range_floating_point<float>(1987.67f, 0.9876f);
  test_range_floating_point<float>(4580.8f, 19823.1f);

}

TEST_CASE( "ranges works for doubles", "[stats]") {

  test_range_floating_point<double>(0.001f, 0.00f);
  test_range_floating_point<double>(10000.0f, 9.0089f);
  test_range_floating_point<double>(1987.67f, 0.9876f);
  test_range_floating_point<double>(4580.8f, 19823.1f);

}

}
