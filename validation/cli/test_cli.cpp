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
  .function = []() { M_benchmarkRunStatus[groupNum - 1][benchmarkNum - 1]++; },\
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

#define NON_EXISTENT_GROUP "ah"
#define NON_EXISTENT_BENCHMARK "bh"
#define NON_EXISTENT_BENCHMARK_FULL_NAME "ah:bh"

namespace {

[[nodiscard]]
constexpr
std::size_t 
M_runNum(std::size_t groupNum, std::size_t benchmarkNum) noexcept {
  return groupNum * benchmarkNum;
}

std::array<std::array<std::size_t, BENCHMARK_NUM>, GROUP_NUM> M_benchmarkRunStatus;

CREATE_ALL;

void
M_resetBenchmarkRunStatus(void) noexcept {
  for (auto& groupStatus : M_benchmarkRunStatus) {
    for (auto& status : groupStatus) {
      status = 0;
    }
  }
}

[[nodiscard]]
std::string
M_benchmarkRunStr(std::string_view benchmarkName, std::size_t runNum) noexcept {
  std::stringstream ss;
  ss << "Starting benchmark: " << benchmarkName << " for: " << runNum << " runs\n";
  for (std::size_t i = 1; i <= runNum; i++) {
    ss << "Run: " << i << '\n';
  }
  ss << "Finished benchmark: " << benchmarkName << " for: " << runNum << " runs\n";
  return ss.str();
}

[[nodiscard]]
std::string
M_groupRunStr(std::size_t groupNum) {
  std::string groupName = "Group_" + std::to_string(groupNum);
  std::stringstream ss;
  ss << "Starting group: " << groupName << '\n';
  for (std::size_t i = 1; i <= BENCHMARK_NUM; i++) {
    ss << M_benchmarkRunStr(groupName + ":Test_" + std::to_string(i), M_runNum(groupNum, i));
  }
  ss << "Finished group: " << groupName << '\n';
  return ss.str();
}

void
M_checkGroupRanCorrectly(std::size_t groupNum) {
  for (std::size_t i = 1; i <= BENCHMARK_NUM; i++) {
    REQUIRE(M_benchmarkRunStatus[groupNum - 1][i - 1] == M_runNum(groupNum, i));
  }
}

class ConsoleOutBuffer {
private:
  std::ostringstream stdoutBuffer, stderrBuffer;
  std::streambuf* const oldStdoutBuffer;
  std::streambuf* const oldStderrBuffer;

public:
  ConsoleOutBuffer(void) 
  : oldStdoutBuffer(std::cout.rdbuf()), oldStderrBuffer(std::cerr.rdbuf()) {
    std::cout.rdbuf(stdoutBuffer.rdbuf());
    std::cerr.rdbuf(stderrBuffer.rdbuf());
  }

  ~ConsoleOutBuffer(void) {
    std::cout.rdbuf(oldStdoutBuffer);
    std::cerr.rdbuf(oldStderrBuffer);
  }
  
  [[nodiscard]]
  std::string
  stdoutStr(void) const {
    return stdoutBuffer.str();
  }

  [[nodiscard]]
  std::string
  stderrStr(void) const {
    return stderrBuffer.str();
  }
  
  void
  reqStdoutEmpty(void) {
    if (stdoutBuffer.tellp() != 0) {
      REQUIRE(stdoutBuffer.str() == ""); // the testing framework will show the stoudBuffer now
    }
  }

  void
  reqStderrEmpty(void) {
    if (stderrBuffer.tellp() != 0) {
      REQUIRE(stderrBuffer.str() == "");
    }
  }
};

}

TEST_CASE( "Help | -h", "[cli]") {
  
  ConsoleOutBuffer outBuffer;

  SECTION( "correct" ) {
    const char* emptyInput[] = {"", benchpp::CLI_OPT_HELP.data()};
    const char** p_emptyInput = emptyInput;
    benchpp::parse_cli_input(2, p_emptyInput);

    outBuffer.reqStderrEmpty(); // This is the more useful way to see the errors
    REQUIRE(outBuffer.stdoutStr() == "Need to implement this\n");
    // i.e in this case if everything is going to std::cerr, then the REQUIRE... line will just show "" != ...
  }

  SECTION( "with extra arg" ) {
    const char* emptyInput[] = {"", benchpp::CLI_OPT_HELP.data(), ""};
    const char** p_emptyInput = emptyInput;
    benchpp::parse_cli_input(3, p_emptyInput);

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == "Need to implement this\n");
  }

}

TEST_CASE( "List all | -l", "[cli]" ) {
  
  ConsoleOutBuffer outBuffer;

  SECTION( "correct" ) {
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_ALL_BENCHMARKS.data()};
    const char** p_input = input;
    benchpp::parse_cli_input(2, p_input);

    auto correctFullListOutput = []() {
      std::stringstream ss;
      for (std::size_t groupNum = 1; groupNum <= GROUP_NUM; groupNum++) {
        for (std::size_t benchmarkNum = 1; benchmarkNum <= BENCHMARK_NUM; benchmarkNum++) {
          ss << "Group_" << groupNum << ":Test_" << benchmarkNum << "   runs:" << M_runNum(groupNum, benchmarkNum) << "\n";
        }
      }
      return ss.str();
    };

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctFullListOutput());
  }

  SECTION( "incorrect" ) {
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_ALL_BENCHMARKS.data(), "aaah"};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(3, p_input));

    outBuffer.reqStdoutEmpty();
    REQUIRE(outBuffer.stderrStr() == "[Error]: Usage: (Benchmark cmd) -l\n");
  }
}

TEST_CASE( "List group | -lg", "[cli]" ) {

  ConsoleOutBuffer outBuffer;
  
  SECTION( "all" ) {
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_GROUP_INFOS.data()};
    const char** p_input = input;
    benchpp::parse_cli_input(2, p_input);

    auto correctOutput = []() {
      std::stringstream ss;
      ss << "Found " << GROUP_NUM << " groups\n";

      for (std::size_t i = 1; i <= GROUP_NUM; i++) {
        ss << "Group_" << i << '\n';
      }
      return ss.str();
    };

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());
  }

  SECTION( "Non existent group" ) {
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_GROUP_INFOS.data(), NON_EXISTENT_GROUP};
    const char** p_input = input;
    benchpp::parse_cli_input(3, p_input);
      
    auto correctOutput = []() {
      std::stringstream ss;
      ss << "0 benchmarks in group: " << NON_EXISTENT_GROUP << '\n';
      return ss.str();
    }; 

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());
  }

  SECTION( "List one group" ) {
    constexpr std::string_view testGroup = "Group_2";
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_GROUP_INFOS.data(), testGroup.data()};
    const char** p_input = input;
    benchpp::parse_cli_input(3, p_input);
      
    auto correctOutput = [&]() {
      std::stringstream ss;
      ss << BENCHMARK_NUM << " benchmarks in group: " << testGroup << '\n';
      for (std::size_t i = 1; i <= BENCHMARK_NUM; i++) {
        ss << "Test_" << i << '\n';
      }
      return ss.str();
    }; 

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());
  }

  SECTION( "List several groups" ) {
    constexpr std::size_t NUM = 3;
    constexpr std::array<std::string_view, NUM> testGroups = { "Group_2", "ah", "Group_3"};
    const char* input[] = {"", benchpp::CLI_OPT_PRINT_GROUP_INFOS.data(), testGroups[0].data(), testGroups[1].data(), testGroups[2].data()};
    const char** p_input = input;
    benchpp::parse_cli_input(2 + NUM, p_input);
      
    auto correctOutput = [&]() {
      std::stringstream ss;
      ss << BENCHMARK_NUM << " benchmarks in group: " << testGroups[0] << '\n';
      for (std::size_t i = 1; i <= BENCHMARK_NUM; i++) {
        ss << "Test_" << i << '\n';
      }
      ss << "0 benchmarks in group: " << testGroups[1] << '\n';
      ss << BENCHMARK_NUM << " benchmarks in group: " << testGroups[2] << '\n';
      for (std::size_t i = 1; i <= BENCHMARK_NUM; i++) {
        ss << "Test_" << i << '\n';
      }
      return ss.str();
    }; 

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());
  }
}

TEST_CASE( "Run benchmark | -b", "[cli]" ) {
  
  ConsoleOutBuffer outBuffer;

  SECTION( "incorrect" ) {
    const char* input[] = {"", benchpp::CLI_OPT_RUN_BENCHMARK.data()};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(2, p_input));

    outBuffer.reqStdoutEmpty();
    REQUIRE(outBuffer.stderrStr() == "[Error]: Usage: (Benchmark cmd) -b (group:benchmark1) (group:benchmark2) (group:benchmark3)\n");
  }

  SECTION( "non existent benchmark" ) {
    const char* input[] = {"", benchpp::CLI_OPT_RUN_BENCHMARK.data(), NON_EXISTENT_BENCHMARK_FULL_NAME};
    const char** p_input = input;
    try {
      benchpp::parse_cli_input(3, p_input);
      REQUIRE(true == false);
    }
    catch(benchpp::BenchmarkNotRegisteredErr& e) {
      REQUIRE(e.groupName == NON_EXISTENT_GROUP);
      REQUIRE(e.name == NON_EXISTENT_BENCHMARK);
    }

    auto benchmarkNotFoundOutput = []() {
      std::stringstream ss;
      ss << "No registered benchmark found with name: " << NON_EXISTENT_BENCHMARK_FULL_NAME << '\n';
      return ss.str();
    };

    outBuffer.reqStdoutEmpty();
    REQUIRE(outBuffer.stderrStr() == benchmarkNotFoundOutput());
  }

  SECTION( "run single benchmark" ) {
    M_resetBenchmarkRunStatus();

    constexpr std::size_t groupNum = 1;
    constexpr std::size_t benchmarkNum = 2;
    constexpr std::string_view testBenchmark = "Group_1:Test_2";
    constexpr std::size_t runNum = M_runNum(groupNum, benchmarkNum);
    const char* input[] = {"", benchpp::CLI_OPT_RUN_BENCHMARK.data(), testBenchmark.data()};
    const char** p_input = input;

    benchpp::parse_cli_input(3, p_input);

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == M_benchmarkRunStr(testBenchmark, runNum));
    REQUIRE(M_benchmarkRunStatus[groupNum - 1][benchmarkNum - 1] == runNum);
  }

  SECTION( "run several benchmarks" ) {
    M_resetBenchmarkRunStatus();

    constexpr std::size_t NUM = 3;
    constexpr std::array<std::size_t, NUM> groupNums = {1, 3, 4};
    constexpr std::array<std::size_t, NUM> benchmarkNums = {2, 1, 4};
    constexpr std::array<std::string_view, NUM> benchmarkNames = 
      { "Group_1:Test_2",
        "Group_3:Test_1",
        "Group_4:Test_4"
      };
    std::array<std::size_t, NUM> runNums{};
    for (std::size_t i = 0; i < NUM; i++) {
      runNums[i] = M_runNum(groupNums[i], benchmarkNums[i]);
    }

    const char* input[] = {"", benchpp::CLI_OPT_RUN_BENCHMARK.data(), benchmarkNames[0].data(), benchmarkNames[1].data(), benchmarkNames[2].data()};
    const char** p_input = input;

    benchpp::parse_cli_input(2 + NUM, p_input);

    auto correctOutput = [&]() {
      std::stringstream ss;
      for (std::size_t i = 0; i < NUM; i++) {
        ss << M_benchmarkRunStr(benchmarkNames[i], runNums[i]);
      }
      return ss.str();
    };

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());

    auto checkBenchmarksRanCorrectly = [&]() {
      for (std::size_t i = 0; i < NUM; i++) {
        REQUIRE(M_benchmarkRunStatus[groupNums[i] - 1][benchmarkNums[i] - 1] == runNums[i]);
      }
    };
    checkBenchmarksRanCorrectly();
  }
}
TEST_CASE( "Run group | -g", "[cli]" ) {
  
  ConsoleOutBuffer outBuffer;
  
  SECTION( "incorrect" ) {
    const char* input[] = {"", benchpp::CLI_OPT_RUN_GROUP.data()};
    const char** p_input = input;
    TERMINATE_CATCHER(benchpp::parse_cli_input(2, p_input));

    outBuffer.reqStdoutEmpty();
    REQUIRE(outBuffer.stderrStr() == "[Error]: Usage: (Benchmark cmd) -g (group1) (group2) (group3)\n");
  }

  SECTION( "non existent group" ) {
    constexpr std::string_view nonExistentGroup = "ahah";
    const char* input[] = {"", benchpp::CLI_OPT_RUN_GROUP.data(), nonExistentGroup.data()};
    const char** p_input = input;
    benchpp::parse_cli_input(3, p_input);

    auto correctNonExistGroupOutput = [&]() {
      std::stringstream ss;
      ss << "Starting group: " << nonExistentGroup << '\n' << "Finished group: " << nonExistentGroup << '\n';
      return ss.str();
    };

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctNonExistGroupOutput());
  }

  SECTION( "single group" ) {
    M_resetBenchmarkRunStatus();
    constexpr std::size_t groupNum = 3;
    constexpr std::string_view group = "Group_3";
    const char* input[] = {"", benchpp::CLI_OPT_RUN_GROUP.data(), group.data()};
    const char** p_input = input;
    benchpp::parse_cli_input(3, p_input);
    
    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == M_groupRunStr(groupNum));
    
    M_checkGroupRanCorrectly(groupNum);
  }

  SECTION( "run several groups" ) {
    M_resetBenchmarkRunStatus();

    constexpr std::size_t NUM = 3;
    constexpr std::array<std::size_t, NUM> groupNums = {1, 3, 4};
    constexpr std::array<std::string_view, NUM> groupNames = 
      { "Group_1",
        "Group_3",
        "Group_4"
      };

    const char* input[] = {"", benchpp::CLI_OPT_RUN_GROUP.data(), groupNames[0].data(), groupNames[1].data(), groupNames[2].data()};
    const char** p_input = input;
  
    try {
      benchpp::parse_cli_input(2 + NUM, p_input);
    }
    catch(...) {
    }

    auto correctOutput = [&]() {
      std::stringstream ss;
      for (std::size_t i = 0; i < NUM; i++) {
        ss << M_groupRunStr(groupNums[i]);
      }
      return ss.str();
    };

    outBuffer.reqStderrEmpty();
    REQUIRE(outBuffer.stdoutStr() == correctOutput());

    auto checkBenchmarksRanCorrectly = [&]() {
      for (std::size_t i = 0; i < NUM; i++) {
        M_checkGroupRanCorrectly(groupNums[i]);
      }
    };

    checkBenchmarksRanCorrectly();
  }
}
