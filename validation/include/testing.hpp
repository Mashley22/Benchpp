#ifndef TESTING_HPP
#define TESTING_HPP

#define TERMINATE_CATCHER(thing) \
{ bool hasTerminated = false; \
try { \
  thing; \
} \
catch(benchpp::priv::TerminateCalled& e) { \
  hasTerminated = true; \
} \
REQUIRE(hasTerminated == true); }

#endif /* TESTING_HPP */
