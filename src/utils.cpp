module;

#ifndef BENCHPP_TEST
#include <exception>
#else
#include <cassert>
#endif

module Benchpp;

namespace benchpp {

namespace priv {

void
terminate(void) {
  #ifndef BENCHPP_TEST
  std::terminate();
  #else
  throw TerminateCalled{};
  #endif
}

}

}
