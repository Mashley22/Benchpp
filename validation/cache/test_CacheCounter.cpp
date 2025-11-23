#include <Bench++/cache.hpp>

#include <catch2/catch_test_macros.hpp>

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

#define ALL_RES_TESTS(type, operation) \
  GENERATE_TEST_TEMPLATE(Event({type, operation, Result::ACCESS})); \
  GENERATE_TEST_TEMPLATE(Event({type, operation, Result::MISS}));

#define ALL_OPS_TESTS(type) \
  ALL_RES_TESTS(type, Operation::READ); \
  ALL_RES_TESTS(type, Operation::WRITE); \
  ALL_RES_TESTS(type, Operation::PREFETCH);

#define ALL_TESTS \
  ALL_OPS_TESTS(Type::L1D);\
  ALL_OPS_TESTS(Type::L1I);\
  ALL_OPS_TESTS(Type::LL);\
  ALL_OPS_TESTS(Type::DTLB);\
  ALL_OPS_TESTS(Type::ITLB);\

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
