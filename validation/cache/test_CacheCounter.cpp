#include <catch2/catch_test_macros.hpp>

#include <Bench++/macros.hpp>

import Benchpp;

#define GENERATE_TEST_TEMPLATE(event) \
  TEST_CASE( event.toStr() , "[cache][!mayfail]" ) { \
    Counter<event> counter; \
    \
    SECTION("Basic getters") { \
      M_checkTemplateMatchesGetters<event>(counter); \
    } \
    \
    SECTION("Read directly after start is 0") { \
    M_checkStartReadIsEmpty<event>(counter);\
    }\
  }

#define ALL_TESTS BENCHPP_CACHE_EVENT_ALL_GENERATOR(GENERATE_TEST_TEMPLATE)

namespace benchpp {

namespace cache {

namespace {

template<Event T_evt>
void
M_checkTemplateMatchesGetters(const Counter<T_evt>& counter) {
  REQUIRE(counter.operation() == T_evt.op);
  REQUIRE(counter.result() == T_evt.res);
  REQUIRE(counter.type() == T_evt.type);
}

template<Event T_evt>
void
M_checkStartReadIsEmpty(Counter<T_evt>& counter) {
  counter.start();
  REQUIRE(counter.read() >= 0);
  counter.stop();
}

}

ALL_TESTS;

}

}
