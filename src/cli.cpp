module;

#include <iostream>
#include <cstdlib>
#include <unordered_map>

module Benchpp;
import :cli;
import :priv.registry;

#define ERROR std::cerr << "[Error]: "

#define USAGE_ERROR ERROR << "Usage: (Benchmark cmd) "

namespace benchpp {

namespace {

// i.e. -b group1 gives argc = 2, argv = {"-b", "group1"}
struct Opt_args {
  int argc;
  char ** argv;
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
M_is_opt(char* arg) {
  return (arg[0] == '-');
}

void
M_print_all_benchmarks(const Opt_args& opt_args) {
  if (opt_args.argc != 1) {
    USAGE_ERROR << BENCHPP_CLI_OPT_PRINT_ALL_BENCHMARKS << '\n';
    std::terminate();
  }
  
  priv::print_all_benchmarks();
}

void
M_print_group_infos(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    USAGE_ERROR << BENCHPP_CLI_OPT_PRINT_GROUP_INFOS << " (group1) (group2) (group3)" << '\n';
    std::terminate();
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    priv::print_all_benchmarks_in_group(opt_args.argv[i]);
  }
}

void 
M_run_groups(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    USAGE_ERROR << BENCHPP_CLI_OPT_RUN_GROUP << " (group1) (group2) (group3)" << '\n';
    std::terminate();
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    priv::run_group(opt_args.argv[i]);
  }
}

void
M_run_benchmark(const Opt_args& opt_args) {
  if (opt_args.argc == 1) {
    USAGE_ERROR << BENCHPP_CLI_OPT_RUN_BENCHMARK << " (group:benchmark1) (group:benchmark2) (group:benchmark3)" << '\n';
    std::terminate();
  }

  for (std::size_t i = 1; i < opt_args.argc; i++) {
    BenchmarkFullName parsedNames(opt_args.argv[i]);
    priv::run_benchmark(parsedNames.group, parsedNames.name);
  }
}

void
M_print_help(const Opt_args& opt_args) {
  (void)opt_args;
  std::cout << "Need to implement this";
}

void
M_invalid_option(const Opt_args& opt_args) {
  (void)opt_args;
  std::cout << "Invalid option, use -h for help";
}

class Parser {
private:
  int m_argc;
  char ** m_argv;
  int m_currentIdx{1};
  const std::unordered_map<std::string_view, void(*)(const Opt_args&)> m_optMap{
    {BENCHPP_CLI_OPT_PRINT_ALL_BENCHMARKS, &M_print_all_benchmarks},
    {BENCHPP_CLI_OPT_PRINT_GROUP_INFOS, &M_print_group_infos},
    {BENCHPP_CLI_OPT_RUN_GROUP, &M_run_groups},
    {BENCHPP_CLI_OPT_RUN_BENCHMARK, &M_run_benchmark},
    {BENCHPP_CLI_OPT_HELP, &M_print_help},
  };

public:
Parser() = delete;
Parser(const int argc, char ** argv) :
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
      std::terminate();
    }
  }
}

};

}

void
parse_cli_input(int argc, char ** argv) {
  Parser parser(argc, argv);
  parser.parse();
}

}
