#ifndef BENCHPP_MACROS_HPP
#define BENCHPP_MACROS_HPP

//_____________________CACHE______________________
//
// TODO: make these macros more useful - tempting but not all combinations are actually always available
// expr is a macro that takes in Event as a parameter,
// this macro does expr over all event with specified type and operation
#define BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, operation) \
  expr(benchpp::cache::Event({type, operation, benchpp::cache::Result::ACCESS})); \
  expr(benchpp::cache::Event({type, operation, benchpp::cache::Result::MISS}));

// same as before but over all results and operations for a given type
#define BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, type) \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::READ); \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::WRITE); \
  BENCHPP_CACHE_EVENT_RESULT_ALL_GENERATOR(expr, type, benchpp::cache::Operation::PREFETCH);

// same as before but over all possible Event structs
#define BENCHPP_CACHE_EVENT_ALL_GENERATOR(expr) \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::L1D); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::L1I); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::LL); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::DTLB); \
  BENCHPP_CACHE_EVENT_RESULT_OPERATION_ALL_GENERATOR(expr, benchpp::cache::Type::ITLB); \

#define BENCHPP_METRIC_ALL_GENERATOR(macro) \
    macro(benchpp::Metric::HW_CPU_CYCLES); \
    macro(benchpp::Metric::CACHE_REFERENCES); \
    macro(benchpp::Metric::CACHE_MISSES); \
    macro(benchpp::Metric::BRANCH_INSTRUCTIONS); \
    macro(benchpp::Metric::BRANCH_MISSES); \
    macro(benchpp::Metric::STALLED_CYCLES_FRONTEND); \
    macro(benchpp::Metric::STALLED_CYCLES_BACKEND); \
    macro(benchpp::Metric::PAGE_FAULTS); \
    macro(benchpp::Metric::CONTEXT_SWITCHES); \
    macro(benchpp::Metric::CPU_MIGRATIONS);

#define REGISTER_BENCHMARK(benchmark) \
static bool benchmark##_registered_var = []() { \
  benchpp::register_benchmark(benchmark); \
  return true; \
}()\

#define BENCHPP_BENCHMARK_GROUP_AND_NAME_STREAM(group_macro_val, name_macro_val)\
  group_macro_val << ":" << name_macro_val

#endif /* BENCHPP_MACROS_HPP */
