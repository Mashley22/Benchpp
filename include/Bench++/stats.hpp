#ifndef BENCHPP_STATS_HPP
#define BENCHPP_STATS_HPP

#include <span>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include <Bench++/assert.hpp>

namespace benchpp {

template<class T>
struct Stats {
  T mean;
  T variance;
  T min;
  T max;
  T median;
  std::size_t count;

  [[nodiscard]] 
  static Stats<T>
  generate(const std::span<const T> results) {

    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");
    ASSERT(!results.empty());

    Stats<T> stats;

    T mean_of_squares = {};
    T mean = {};
    T min = results[0];
    T max = results[0];
    for (std::size_t i = 0; i < results.size(); i++) {
      mean_of_squares += results[i] * results[i];
      mean += results[i];

      if (results[i] < min) {
        min = results[i];
      }

      if (results[i] > max) {
        max = results[i];
      }
    }
    mean_of_squares = mean_of_squares / static_cast<T>(results.size());
    mean = mean / static_cast<T>(results.size());

    stats.mean = mean;
    stats.variance = mean_of_squares - mean * mean;
    stats.max = max;
    stats.min = min;

    stats.median = calc_median(results);
    stats.count = results.size();

    return stats;
  }
  
  [[nodiscard]]
  static T 
  calc_median(const std::span<const T> results) {

    std::vector<T> copy(results);

    std::sort(copy.begin(), copy.end());

    if (results.size() % 2 == 0) {
      return copy[results.size() / 2];
    }
    else {
      return (copy[results.size() / 2] + copy[results.size() / 2 + 1]) / 2;
    }
  }
  
  [[nodiscard]]
  T
  range(void) const noexcept {
    return max - min;
  }
  
  [[nodiscard]]
  T
  stddev(void) const noexcept {
    return std::sqrt(variance);
  }
  
  void
  print(void) const {
    std::cout 
    << "Sample count: " << count << '\n'
    << "Mean: " << mean << '\n'
    << "Variance: " << variance << '\n'
    << "Standard deviation: " << stddev() << '\n'
    << "Min: " << min << '\n'
    << "Max: " << max << '\n'
    << "Range: " << range() << '\n'
    << "Median: " << median << '\n';
  }
};

}

#endif /* BENCHPP_STATS_HPP */
