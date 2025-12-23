module;

#ifndef BENCHPP_TEST
#include <exception>
#else
#include <cassert>
#endif

module Benchpp;

namespace benchpp {

namespace priv {

namespace {

bool M_hasTerminated = false;

}

void
terminate(void) {
  #ifndef BENCHPP_TEST
  std::terminate();
  #else
  assert(M_hasTerminated == false && "Terminate not caught!");
  M_hasTerminated = true;
  #endif
}

#ifdef BENCHPP_TEST
bool
has_terminated(void) {
  return M_hasTerminated;
}

void 
undo_terminate(void) {
  assert(M_hasTerminated && "Not currently terminated!");
  M_hasTerminated = false;
}
#endif

}

}
