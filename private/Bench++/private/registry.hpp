#ifndef BENCHPP_PRIVATE_REGISTRY_HPP
#define BENCHPP_PRIVATE_REGISTRY_HPP

#include <Bench++/registry.hpp>

namespace benchpp {

namespace priv {

void
add_benchmark(const BenchmarkInfo &info);

void 
run_benchmark(const BenchmarkInfo& benchmark);

void 
run_benchmark(const BenchmarkInfo& benchmark, const std::size_t runNum);

void
run_benchmark(const std::string_view name);

void
run_benchmark(const std::string_view name, const std::size_t runNum);

}

}
#endif /* BENCHPP_PRIVATE_REGISTRY_HPP */
