#include <Bench++/cache.hpp>

#include <catch2/catch_test_macros.hpp>

namespace benchpp {

namespace cache {
TEST_CASE( "", "[Cache::Counter]" ) {
  constexpr Event evt {
    .type = Type::LL,
    .op = Operation::READ,
    .res = Result::MISS
  };

  Counter<evt> counter;

}

}

}
