#ifndef BENCHPP_STATS_HPP
#define BENCHPP_STATS_HPP

#include <span>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>

namespace benchpp {

template<class T, class D = double>
struct Stats {
  std::size_t count;
  D mean;
  D variance;
  D median;
  T min;
  T max;

  [[nodiscard]] 
  static Stats<T, D>
  generate(const std::span<const T> results) {

    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");
    assert(!results.empty());

    Stats<T> stats;

    T sum_of_squares = {};
    T mean = {};
    T min = results[0];
    T max = results[0];
    for (std::size_t i = 0; i < results.size(); i++) {
      sum_of_squares += results[i] * results[i];
      mean += results[i];

      if (results[i] < min) {
        min = results[i];
      }

      if (results[i] > max) {
        max = results[i];
      }
    }
    D mean_of_squares = static_cast<D>(sum_of_squares) / static_cast<D>(results.size());
    stats.mean = static_cast<D>(mean) / static_cast<D>(results.size());

    stats.variance = mean_of_squares - stats.mean * stats.mean;
    stats.max = max;
    stats.min = min;

    stats.median = calc_median<D>(results);
    stats.count = results.size();

    return stats;
  }
  
  template<class R = double>
  [[nodiscard]]
  static R  // not sure about this
  calc_median(const std::span<const T> results) {

    static_assert(std::is_arithmetic_v<R>);

    std::vector<T> copy(results.begin(), results.end());

    std::sort(copy.begin(), copy.end());

    if (results.size() % 2 == 0) {
      return static_cast<R>(copy[results.size() / 2] + copy[results.size() / 2 - 1]) / 2;
    }
    else {
      return static_cast<R>(copy[(results.size() - 1) / 2]);
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
    return static_cast<T>(std::sqrt(variance));
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
