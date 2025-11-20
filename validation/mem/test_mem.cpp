#include <Bench++/mem.hpp>

#include <catch2/catch_test_macros.hpp>

namespace benchpp {

TEST_CASE( "memory utility functions", "[mem]" ) {

  SECTION("Basic") {
    REQUIRE(mem::get_currentVirtual() > 0);
    REQUIRE(mem::get_currentPhysical() > 0);
    REQUIRE(mem::get_currentSwapped() == 0); // perhaps disengenuous but oh well

    REQUIRE(mem::get_peakVirtual() > 0);
    REQUIRE(mem::get_peakPhysical() > 0);

    REQUIRE(mem::try_get_currentVirtual().value() > 0);
    REQUIRE(mem::try_get_currentPhysical().value() > 0);
    REQUIRE(mem::try_get_currentSwapped().value() == 0);

    REQUIRE(mem::try_get_peakVirtual().value() > 0);
    REQUIRE(mem::try_get_peakPhysical().value() > 0);
  }

  SECTION("Snapshots") {
    mem::Snapshot snapshot = mem::get_snapshot();
    REQUIRE(snapshot.phy > 0);
    REQUIRE(snapshot.virt > 0);
    REQUIRE(snapshot.swap == 0);

    snapshot = mem::try_get_snapshot().value();

    REQUIRE(snapshot.phy > 0);
    REQUIRE(snapshot.virt > 0);
    REQUIRE(snapshot.swap == 0);
  }

}

}
