#include <iostream>
#include <sstream>
#include <array>

#include <catch2/catch_test_macros.hpp>

import Benchpp;

#include <Bench++/macros.hpp>
#include <testing.hpp>

#define GROUP_NUM 5
#define BENCHMARK_NUM 5

#define CREATE_TEST_BENCHMARK(groupNum, benchmarkNum) \
benchpp::BenchmarkInfo info_##groupNum##_##benchmarkNum = { \
  .name = "Test_" #benchmarkNum,\
  .group = "Group_" #groupNum, \
  .function = []() { M_benchmarkRunStatus[groupNum][benchmarkNum]++; },\
  .runNum = M_runNum(groupNum, benchmarkNum) \
}; \
REGISTER_BENCHMARK(info_##groupNum##_##benchmarkNum);

#define CREATE_GROUP(num) \
CREATE_TEST_BENCHMARK(num, 1); \
CREATE_TEST_BENCHMARK(num, 2); \
CREATE_TEST_BENCHMARK(num, 3); \
CREATE_TEST_BENCHMARK(num, 4); \
CREATE_TEST_BENCHMARK(num, 5);

#define CREATE_ALL \
CREATE_GROUP(1) \
CREATE_GROUP(2) \
CREATE_GROUP(3) \
CREATE_GROUP(4) \
CREATE_GROUP(5) 

namespace {

[[nodiscard]]
std::size_t 
M_runNum(std::size_t groupNum, std::size_t benchmarkNum) noexcept {
  return groupNum * benchmarkNum;
}

std::array<std::array<int, BENCHMARK_NUM>, GROUP_NUM> M_benchmarkRunStatus;

CREATE_ALL;

}

TEST_CASE( "Test correct outprinting", "[cli]" ) {

  std::ostringstream stdoutBuffer;
  std::streambuf* oldBuffer;

  oldBuffer = std::cout.rdbuf(stdoutBuffer.rdbuf());

  SECTION( "help" ) {
    const char* emptyInput[] = {"", "-h"};
    const char** p_emptyInput = emptyInput;
    benchpp::parse_cli_input(2, p_emptyInput);
    REQUIRE(stdoutBuffer.str() == "Need to implement this\n");
  }

  SECTION( "-l" ) {
    const char* input[] = {"", "-l"};
    const char** p_input = input;
    benchpp::parse_cli_input(2, p_input);
  }

  std::cout.rdbuf(oldBuffer);
}

TEST_CASE( "Test incorreclt cli inputs", "[cli]" ) {

  std::ostringstream stderrBuffer;
  std::streambuf* oldBuffer;

  oldBuffer = std::cerr.rdbuf(stderrBuffer.rdbuf());

  SECTION( "-l incorrectly" ) {
    const char* input[] = {"", "-l", "aaah"};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(3, p_input));
    REQUIRE(stderrBuffer.str() == "[Error]: Usage: (Benchmark cmd) -l\n");
  }

  SECTION( "-g incorrectly" ) {
    const char* input[] = {"", "-g"};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(3, p_input));
    REQUIRE(stderrBuffer.str() == "[Error]: Usage: (Benchmark cmd) -g (group1) (group2) (group3)\n");
  }

  SECTION( "-b incorrectly" ) {
    const char* input[] = {"", "-b"};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(3, p_input));
    REQUIRE(stderrBuffer.str() == "[Error]: Usage: (Benchmark cmd) -b (group:benchmark1) (group:benchmark2) (group:benchmark3)\n");
  }

  std::cerr.rdbuf(oldBuffer);
}
