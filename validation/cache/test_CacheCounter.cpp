#include <Bench++/cache.hpp>

#include <catch2/catch_test_macros.hpp>

namespace benchpp {

namespace cache {

TEST_CASE( "", "[Cache::Counter]" ) {

  Counter<{Type::LL, Operation::READ, Result::MISS}> counter;

  SECTION( "" ) {
    counter.start();
    REQUIRE(counter.read() == 0);
  }

}

}

}
