#include <Bench++/events.hpp>

#include <catch2/catch_test_macros.hpp>

#define POINT_COUNT 100
#define RUN_COUNT 1000

#define INIT_VAL POINT_COUNT * RUN_COUNT + 1

namespace benchpp {

struct TestObj {
  std::uint64_t num;

  TestObj(void) noexcept :
    num(INIT_VAL) {}

  TestObj(std::uint64_t val) :
    num(val) {}
};

TEST_CASE( "EventRecord", "[EventRecord]" ) {
  EventsRecord<TestObj, POINT_COUNT, RUN_COUNT> record;

  SECTION( "Basics" ) {
    REQUIRE(record.runCount() == RUN_COUNT);
    REQUIRE(record.pointCount() == POINT_COUNT);
    REQUIRE(record.totalEvents() == POINT_COUNT * RUN_COUNT);
  }

  SECTION( "All objs are default initialized" ) {
    for (std::size_t i = 0; i < RUN_COUNT; i++) {
      for (const auto& x : record.get_run(i)) {
        REQUIRE(x.num == INIT_VAL);
      }
    }
  }

  SECTION( "Rest of the stuff" ) {
    std::uint64_t val = 0;
    for (std::size_t i = 0; i < RUN_COUNT; i++) {
      for (std::size_t j = 0; j < POINT_COUNT; j++) {
        record.push_back(TestObj{val});
        REQUIRE(record.get_run(i)[j].num == val);
        val++;
      }
    }

    val = 0;
    for (std::size_t i = 0; i < RUN_COUNT; i++) {
      for (std::size_t j = 0; j < POINT_COUNT; j++) {
        REQUIRE(record.get_run(i)[j].num == val);
        val++;
      }
    }
  }
}

}
