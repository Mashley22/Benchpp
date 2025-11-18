#ifndef BENCHPP_ASSERT_HPP
#define BENCHPP_ASSERT_HPP

#ifdef BENCHPP_TEST
#include <string_view>
#include <catch2/catch_test_macros.hpp>

namespace benchpp {

struct AssertFail {
  std::string_view cond;
  std::string_view msg;
};

}
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            throw benchpp::AssertFail{#condition, ""}; \
        } \
    } while(0)

// Assert with custom message
#define ASSERT_MSG(condition, message) \
    do { \
        if (!(condition)) { \
            throw benchpp::AssertFail{#condition, message}; \
        } \
    } while(0)

#define EXPECTED_ASSERT_BUT_NONE(func) REQUIRE_FALSE(True << "Expected assert in #func, but none found")

#define ASSERT_HANDLER(func) \
  do { \
    try { \
      func; \
      EXPECTED_ASSERT_BUT_NONE(func);
    catch(Benchpp::AssertFail a) { \
    } \
  } while(0)

#define ASSERT_HANDLER_DETAILED(func, cond, msg) \
  do { \
    try { \
      func; \
      EXPECTED_ASSERT_BUT_NONE(func);
    catch(Benchpp::AssertFail a) { \
      REQUIRE(a.cond == cond);
      REQUIRE(a.msg == msg);
    } \
  } while(0)

#else

#include <iostream>

#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "File: " << __FILE__ << std::endl; \
            std::cerr << "Line: " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while(0)

// Assert with custom message
#define ASSERT_MSG(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "Message: " << message << std::endl; \
            std::cerr << "File: " << __FILE__ << std::endl; \
            std::cerr << "Line: " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while(0)
#endif

#endif /* BENCHPP_ASSERT_HPP */
