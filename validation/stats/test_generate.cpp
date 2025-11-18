#include <Bench++/stats.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <array>
#include <cstdint>

namespace benchpp {

namespace {

template<class T>
void
check_stats_equal(const Stats<T>& a, const Stats<T>& b) noexcept {
  REQUIRE(a.count == b.count);
  REQUIRE(a.min == b.min);
  REQUIRE(a.max == b.max);
  REQUIRE_THAT(a.median, Catch::Matchers::WithinRel(b.median));
  REQUIRE_THAT(a.mean, Catch::Matchers::WithinRel(b.mean));
  REQUIRE_THAT(a.variance, Catch::Matchers::WithinRel(b.variance));
}

}

TEST_CASE( "generate for unsigned types", "[stats]" ) {

  SECTION( "odd sized arrays" ) {
    std::array<std::uint64_t, 25> arr = {
      87, 12, 45, 63, 29, 91, 54, 8, 76, 33,
      18, 99, 41, 6, 22, 58, 70, 37, 80, 14,
      49, 25, 67, 5, 31
    };
  

    Stats<std::uint64_t> manual = {
      .count = 25,
      .mean = 44.8,
      .variance = 782.16,
      .median = 41,
      .min = 5,
      .max = 99
    };

    Stats<std::uint64_t> gen = Stats<std::uint64_t>::generate(arr);
  
    check_stats_equal(manual, gen);

  }

  SECTION( "even sized arrays" ) {
    std::array<uint64_t, 24> arr = {
      34, 7, 89, 56, 12, 43, 68, 90, 21, 5,
      77, 32, 19, 62, 84, 14, 50, 39, 73, 9,
      26, 41, 61, 17
    };

    Stats<uint64_t> manual = {
      .count = 24,
      .mean = 42.875,
      .variance = 730.609375,
      .median = 40.0,
      .min = 5,
      .max = 90
    };

    Stats<std::uint64_t> gen = Stats<std::uint64_t>::generate(arr);

    check_stats_equal(manual, gen);
  }

}

TEST_CASE( "generate for signed types", "[stats]" ) {

  SECTION( "odd sized arrays" ) {
    std::array<int64_t, 25> arr = {
      -87, 12, -45, 63, 29, -91, 54, -8, 76, -33,
      18, 99, -41, 6, -22, 58, -70, 37, 80, -14,
      49, -25, 67, 5, -31
    };

    Stats<int64_t> manual = {
      .count = 25,
      .mean = 7.44,    
      .variance = 2733.8464,
      .median = 6.0,
      .min = -91,      
      .max = 99        
    };

    Stats<std::int64_t> gen = Stats<std::int64_t>::generate(arr);

    check_stats_equal(manual, gen);
  }
  
  SECTION( "even sized arrays" ) {
    std::array<int64_t, 24> arr = {
      -34, 7, -89, 56, 12, -43, 68, 90, -21, 5,
      77, -32, 19, -62, 84, 14, -50, 39, -73, 9,
      26, -41, 61, -17
    };

    Stats<int64_t> manual = {
      .count = 24,
      .mean = 4.375,
      .variance = 2549.734375,
      .median = 8.0,
      .min = -89,
      .max = 90
    };

    Stats<std::int64_t> gen = Stats<std::int64_t>::generate(arr);

    check_stats_equal(manual, gen);
  }

}


TEST_CASE( "generate for (double) floating points", "[stats]" ) {

  SECTION( "odd sized arrays" ) {
    std::array<double, 25> arr = {
      -87.5, 12.2, -45.1, 63.3, 29.7, -91.8, 54.4, -8.6, 76.0, -33.9,
      18.5, 99.1, -41.3, 6.0, -22.7, 58.6, -70.2, 37.8, 80.4, -14.9,
      49.5, -25.1, 67.3, 5.4, -31.2
    };

    Stats<double> manual = {
      .count = 25,
      .mean = 7.436,
      .variance = 2769.627904,
      .median = 6.0,
      .min = -91.8,
      .max = 99.1
    };

    Stats<double> gen = Stats<double>::generate(arr);

    check_stats_equal(manual, gen);
  }

  SECTION( "even sized arrays" ) {
    std::array<double, 24> arr = {
      -34.5, 7.1, -89.2, 56.6, 12.3, -43.8, 68.9, 90.0, -21.4, 5.2,
      77.3, -32.7, 19.5, -62.1, 84.4, 14.6, -50.0, 39.2, -73.5, 9.8,
      26.4, -41.9, 61.9, -17.3
    };

    Stats<double> manual = {
      .count = 24,
      .mean = 4.45,
      .variance = 2585.9875,
      .median = 8.45,
      .min = -89.2,
      .max = 90.0
    };

    Stats<double> gen = Stats<double>::generate(arr);

    check_stats_equal(manual, gen);
}

}

}
