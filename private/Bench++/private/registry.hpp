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

class GroupRunner {
public:
  GroupRunner() = delete;
  GroupRunner(const std::string_view groupName) noexcept;
  
  /**@retval true if there is another benchmark in the group
   * @retval false if there are no more benchmarks in the group
   */
  bool 
  nextBenchmark(void) noexcept;

  const BenchmarkInfo&
  currentBenchmark(void) const noexcept;

  void
  reset(void) noexcept;
  
private:
  std::string_view m_name;
  std::size_t m_currentIdx{0};
};

}

}
#endif /* BENCHPP_PRIVATE_REGISTRY_HPP */
