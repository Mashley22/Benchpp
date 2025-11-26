#include <Bench++/cache.hpp>

#define TEMPLATE_GENERATOR(evt) template class benchpp::cache::Counter<evt>;

namespace benchpp {

namespace cache {

std::string
type_toStr(const Type& val) {
  switch(val) {
    case Type::L1D:
      return "L1 data";
    case Type::L1I:
      return "L1 instruction";
    case Type::LL:
      return "Lowest level cache";
    case Type::DTLB:
      return "Data TLB";
    case Type::ITLB:
      return "Instruction TLB";
    };
  return "Invalid cache type";
}

std::string
operation_toStr(const Operation& val) {
  switch(val) {
    case Operation::PREFETCH:
      return "Prefetch";
    case Operation::READ:
      return "Read";
    case Operation::WRITE:
      return "Write";
  };
  return "Invalid cache operation";
}

std::string
result_toStr(const Result& val) {
  switch(val) {
    case Result::ACCESS:
      return "Access";
    case Result::MISS:
      return "Miss";
  };
  return "Invalid cache result";
}

std::string
Event::toStr(void) const {
  return type_toStr(type) + " " + operation_toStr(op) + " " + result_toStr(res);
}

}

}

#ifdef __linux__
  #include "linux/cache.hpp"
#endif

BENCHPP_CACHE_EVENT_ALL_GENERATOR(TEMPLATE_GENERATOR);
