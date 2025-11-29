#ifndef BENCHPP_CLI_HPP
#define BENCHPP_CLI_HPP

// These are the same on both the launcher and the execs

#define BENCHPP_CLI_OPT_PRINT_ALL_BENCHMARKS "-l"
/**@brief if nothing specified after will print all the groups
 * if a group is named it will print all info about said group
 */
#define BENCHPP_CLI_OPT_PRINT_GROUP_INFOS "-lg" 

/**@brief follow this with the group name
 */
#define BENCHPP_CLI_OPT_RUN_GROUP "-g"

/**@brief follow this with the benchmark you want to run
 *        and the number of runs if you want to specify
 */
#define BENCHPP_CLI_OPT_RUN_BENCHMARK "-b"

#define BENCHPP_CLI_HELP "-h"

#endif /* BENCHPP_CLI_HPP */
