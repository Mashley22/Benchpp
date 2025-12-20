#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <array>

import Benchpp;

namespace benchpp {

TEST_CASE( "calc_median for unsigned types", "[stats]" ) {

  SECTION( "odd sized array" ) {

    {
    std::array<std::uint64_t, 3> arr{6, 7, 8};
    REQUIRE_THAT(Stats<std::uint64_t>::calc_median(arr), Catch::Matchers::WithinRel(7.0));
    }
  
    {
    std::array<std::uint64_t, 25> arr = {
        87, 12, 45, 63, 29, 91, 54, 8, 76, 33,
        18, 99, 41, 6, 22, 58, 70, 37, 80, 14,
        49, 25, 67, 5, 31
    };

    REQUIRE_THAT(Stats<std::uint64_t>::calc_median(arr), Catch::Matchers::WithinRel(41.0));
    }

  }

  SECTION( "even sized array" ) {

    {
    std::array<std::uint64_t, 4> arr{6, 7, 8, 9};
    REQUIRE_THAT(Stats<std::uint64_t>::calc_median(arr), Catch::Matchers::WithinRel(7.5));
    }
    
    {
    std::array<std::uint64_t, 24> arr = {
        34, 7, 89, 56, 12, 43, 68, 90, 21, 5,
        77, 32, 19, 62, 84, 14, 50, 39, 73, 9,
        26, 41, 61, 17
    };

    REQUIRE_THAT(Stats<std::uint64_t>::calc_median(arr), Catch::Matchers::WithinRel(40.0));
    }

  }

}

TEST_CASE( "calc_median for signed types", "[stats]" ) {

  SECTION( "odd sized array" ) {

    {
    std::array<std::int64_t, 3> arr{6, 7, 8};
    REQUIRE_THAT(Stats<std::int64_t>::calc_median(arr), Catch::Matchers::WithinRel(7.0));
    }
  
    {
    std::array<std::int64_t, 25> arr = {
        -87, 12, -45, 63, 29, -91, 54, -8, 76, -33,
        18, 99, -41, 6, -22, 58, -70, 37, 80, -14,
        49, -25, 67, 5, -31
    };

    REQUIRE_THAT(Stats<std::int64_t>::calc_median(arr), Catch::Matchers::WithinRel(6.0));
    }

  }

  SECTION( "even sized array" ) {

    {
    std::array<std::int64_t, 4> arr{6, 7, 8, 9};
    REQUIRE_THAT(Stats<std::int64_t>::calc_median(arr), Catch::Matchers::WithinRel(7.5));
    }

    {   
    std::array<std::int64_t, 24> arr = {
        -34, 7, -89, 56, 12, -43, 68, 90, -21, 5,
        77, -32, 19, -62, 84, 14, -50, 39, -73, 9,
        26, -41, 61, -17
    };

    REQUIRE_THAT(Stats<std::int64_t>::calc_median(arr), Catch::Matchers::WithinRel(8.0));
    }

  }

}

TEST_CASE( "calc_median for (double) floating point types", "[stats]" ) {

  SECTION( "odd sized array" ) {

    {
    std::array<double, 3> arr{6, 7, 8};
    REQUIRE_THAT(Stats<double>::calc_median(arr), Catch::Matchers::WithinRel(7.0));
    }
  
    {
    std::array<double, 25> arr = {
        -87.5, 12.2, -45.1, 63.3, 29.7, -91.8, 54.4, -8.6, 76.0, -33.9,
        18.5, 99.1, -41.3, 6.0, -22.7, 58.6, -70.2, 37.8, 80.4, -14.9,
        49.5, -25.1, 67.3, 5.4, -31.2
    };

    REQUIRE_THAT(Stats<double>::calc_median(arr), Catch::Matchers::WithinRel(6.0));
    }

  }

  SECTION( "even sized array" ) {

    {
    std::array<double, 4> arr{6, 7, 8, 9};
    REQUIRE_THAT(Stats<double>::calc_median(arr), Catch::Matchers::WithinRel(7.5));
    }

    {   
    std::array<double, 24> arr = {
        -34.5, 7.1, -89.2, 56.6, 12.3, -43.8, 68.9, 90.0, -21.4, 5.2,
        77.3, -32.7, 19.5, -62.1, 84.4, 14.6, -50.0, 39.2, -73.5, 9.8,
        26.4, -41.9, 61.7, -17.3
    };

    REQUIRE_THAT(Stats<double>::calc_median(arr), Catch::Matchers::WithinRel(8.45));
    }

  }

}

}
