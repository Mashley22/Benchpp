module;

#include <cassert>
#include <format>
#include <iostream>

#include <Bench++/macros.hpp>

module Benchpp;
import :priv.registry;

namespace benchpp {

BenchmarkNotRegisteredErr::BenchmarkNotRegisteredErr(const std::string_view groupName_val, const std::string_view name_val) noexcept {
  std::cerr << "No registered benchmark found with name: " << BENCHPP_BENCHMARK_GROUP_AND_NAME_STREAM(groupName_val, name_val) << '\n';
  groupName = groupName_val;
  name = name_val;
}

GroupNotRegisteredErr::GroupNotRegisteredErr(const std::string_view groupName_val) noexcept {
  std::cerr << "No registered group found with name: " << groupName_val << '\n';
  groupName = groupName_val;
}

void
register_benchmark(const BenchmarkInfo &info) {
  priv::register_benchmark(info);
}

std::stringstream
BenchmarkInfo::id_to_sstream(void) const {
  std::stringstream ss;
  ss << BENCHPP_BENCHMARK_GROUP_AND_NAME_STREAM(group, name);

  return ss;
}

std::string
BenchmarkInfo::formatCompletionInfo(void) const {
  assert(p_timer != nullptr);
  assert(!p_timer->times().empty());
  return std::format("=====================\n"
                     "{}:{}\n"
                     "{}", group, name, Stats<TimeCount_t>::generate(p_timer->times()).formatResults());
}


void
BenchmarkInfo::printCompletionInfo(void) const {
  std::cout << formatCompletionInfo() << '\n';
}

}
