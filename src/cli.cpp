module;

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>

module Benchpp;
import :cli;
import :priv.registry;
import :priv.utils;
import :iteration_counter;

#define ERROR std::cerr << "[Error]: "

#define USAGE_ERROR ERROR << "Usage: (Benchmark cmd) "

namespace benchpp {

namespace {

// i.e. -b group1 gives argc = 2, argv = {"-b", "group1"}
struct Opt_args {
  int argc;
  const char ** argv;
};


struct BenchmarkFullName {
  std::string_view group;
  std::string_view name;
  
  void
  fromCombined(const std::string_view str) {
    std::size_t pos = str.find(":");

    if (pos == std::string_view::npos) {
      group = "";
      name = str;
    }
    else {
      group = str.substr(0, pos);
      name = str.substr(pos + 1);
    }
  }

  BenchmarkFullName(const std::string_view str) {
    fromCombined(str);
  }
};


[[nodiscard]]
bool
M_is_opt(const char* arg) {
  return (arg[0] == '-');
}

void
M_print_all_benchmarks(const Opt_args& opt_args) {
  if (opt_args.argc != 1) {
    USAGE_ERROR << CLI_OPT_PRINT_ALL_BENCHMARKS << std::endl;
    priv::terminate();
  }
  
  priv::print_all_benchmarks();
}

void
M_print_group_infos(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    priv::print_all_groups();
    return;
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    priv::print_all_benchmarks_in_group(opt_args.argv[i]);
  }
}

void 
M_run_groups(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    USAGE_ERROR << CLI_OPT_RUN_GROUP << " (group1) (group2) (group3)" << std::endl;
    priv::terminate();
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    priv::run_group(opt_args.argv[i]);
  }
}

void
M_run_benchmark(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    USAGE_ERROR << CLI_OPT_RUN_BENCHMARK << " (group:benchmark1) (group:benchmark2) (group:benchmark3)" << std::endl;
    priv::terminate();
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    BenchmarkFullName parsedNames(opt_args.argv[i]);
    priv::run_benchmark(parsedNames.group, parsedNames.name);
  }
}

void
M_print_help(const Opt_args& opt_args) {
  (void)opt_args;
  std::cout << "Benchpp - C++ lightweight benchmarking and performance monitoring framework\n\n"
            << "USAGE:\n"
            << "  benchmark [OPTION] [ARGUMENTS]\n\n"
            << "OPTIONS:\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_PRINT_ALL_BENCHMARKS 
            << "          List all available benchmarks\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_PRINT_GROUP_INFOS 
            << "          List all groups, or info about specific group(s)\n"
            << "                  " << "Usage: " << CLI_OPT_PRINT_GROUP_INFOS << " [group1] [group2] ...\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_RUN_GROUP 
            << "          Run benchmarks in specified group(s)\n"
            << "                  " << "Usage: " << CLI_OPT_RUN_GROUP << " <group1> [group2] [group3] ...\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_RUN_BENCHMARK 
            << "          Run specific benchmark(s)\n"
            << "                  " << "Usage: " << CLI_OPT_RUN_BENCHMARK << " <group:benchmark1> [group:benchmark2] ...\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_SET_ITERATION_COUNTER 
            << "          Set the number of iterations to run\n"
            << "                  " << "Usage: " << CLI_OPT_SET_ITERATION_COUNTER << " <iteration_num>\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_RUN_ALL
            << "          Run all benchmarks\n"
            << "  " << std::setw(3) << std::left << CLI_OPT_HELP 
            << "          Display this help message\n";
}

void
M_setIterationCounter(const Opt_args& opt_args) {
  if (opt_args.argc != 2) {
    USAGE_ERROR << CLI_OPT_SET_ITERATION_COUNTER << " (iteration num)" << std::endl;
    priv::terminate();
  }
  
  std::size_t num;
  try {
    num = std::stoll(opt_args.argv[1]);
  }
  catch(std::invalid_argument& e) {
    ERROR << opt_args.argv[1] << " is an invalid arguement for the iteration counter" << std::endl;
    priv::terminate();
  }
  catch(std::out_of_range& e) {
    ERROR << opt_args.argv[1] << " is out of range for the iteration counter" << std::endl;
    priv::terminate();
  }
  
  startIteration(num);
}

void
M_runAll(const Opt_args& opt_args) {
  (void)opt_args;
  std::cout << "running all benchmarks!\n";
  priv::run_all();
}

void
M_invalid_option(const Opt_args& opt_args) {
  (void)opt_args;
  std::cout << "Invalid option, use -h for help\n";
}

class Parser {
private:
  int m_argc;
  const char ** m_argv;
  int m_currentIdx{1};
  const std::unordered_map<std::string_view, void(*)(const Opt_args&)> m_optMap{
    {CLI_OPT_PRINT_ALL_BENCHMARKS, &M_print_all_benchmarks},
    {CLI_OPT_PRINT_GROUP_INFOS, &M_print_group_infos},
    {CLI_OPT_RUN_GROUP, &M_run_groups},
    {CLI_OPT_RUN_BENCHMARK, &M_run_benchmark},
    {CLI_OPT_HELP, &M_print_help},
    {CLI_OPT_SET_ITERATION_COUNTER, &M_setIterationCounter},
    {CLI_OPT_RUN_ALL, &M_runAll},
  };

public:
Parser() = delete;
Parser(const int argc, const char ** argv) :
  m_argc(argc), m_argv(argv) {}

private:

[[nodiscard]]
Opt_args
extract_next_args(void) {
  Opt_args retval = {
    .argc = 1,
    .argv = &m_argv[m_currentIdx],
  };

  while (true) {
    std::size_t currentIdx = m_currentIdx + retval.argc;
    if (!(currentIdx < m_argc)) {
      break;
    }

    if (M_is_opt(m_argv[currentIdx])) {
      break;
    }
    else {
      retval.argc++;
    }
  }

  m_currentIdx += retval.argc;

  return retval;
}

public:
void
parse(void) {
  while (m_currentIdx < m_argc) {
    Opt_args next_args = extract_next_args();

    try {
      m_optMap.at(std::string_view(next_args.argv[0]))(next_args);
    }
    catch (const std::out_of_range& e) {
      std::cerr << next_args.argv[0] << " is not a valid option, use -h for more help";
      priv::terminate();
    }
  }
}

};

}

void
parse_cli_input(int argc, const char ** argv) {
  Parser parser(argc, argv);
  parser.parse();
}

}
