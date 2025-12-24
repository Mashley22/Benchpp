module;

#include <string_view>

export module Benchpp:cli;

namespace benchpp {

// These are the same on both the launcher and the execs
export
constexpr std::string_view CLI_OPT_PRINT_ALL_BENCHMARKS = "-l";

/**@brief if nothing specified after will print all the groups
 * if a group is named it will print all info about said group
 */
export
constexpr std::string_view CLI_OPT_PRINT_GROUP_INFOS = "-lg";

/**@brief follow this with the group name / names like group1 group2 etc.
 */
export
constexpr std::string_view CLI_OPT_RUN_GROUP = "-g";

/**@brief follow this with the benchmark you want to run
 *        and the number of runs if you want to specify
 */
export
constexpr std::string_view CLI_OPT_RUN_BENCHMARK = "-b";

export
constexpr std::string_view CLI_OPT_HELP = "-h";

export
constexpr std::string_view CLI_OPT_SET_ITERATION_COUNTER = "-i";

export
void
parse_cli_input(int argc, const char** argv);

}
