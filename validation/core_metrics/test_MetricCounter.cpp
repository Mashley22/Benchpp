#include <Bench++/core_metrics.hpp>

#include <catch2/catch_test_macros.hpp>

#define GENERATE_TEST_TEMPLATE(met) \
  TEST_CASE( metric_toStr(met) , "[core_metrics][!mayfail]" ) { \
    MetricCounter<met> counter; \
    \
    SECTION("Basic getters") { \
      M_checkTemplateMatchesGetters<met>(counter); \
    } \
    \
    SECTION("Read directly after start is 0") { \
    M_checkStartReadIsEmpty<met>(counter);\
    }\
  }

#define ALL_TESTS BENCHPP_METRIC_ALL_GENERATOR(GENERATE_TEST_TEMPLATE)

namespace benchpp {

namespace cache {

namespace {

template<Metric T_metric>
void
M_checkTemplateMatchesGetters(const MetricCounter<T_metric>& val) {
  REQUIRE(val.metric() == T_metric);
}

template<Metric T_metric>
void
M_checkStartReadIsEmpty(MetricCounter<T_metric>& val) {
  val.start();
  REQUIRE(val.read() >= 0);
  val.stop();
}

}

ALL_TESTS;

}

}
