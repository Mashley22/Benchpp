#ifndef BENCHPP_EVENTS_HPP
#define BENCHPP_EVENTS_HPP

#include <concepts>
#include <cstdint>
#include <vector>
#include <cassert>
#include <span>

#define BENCHPP_CONCEPT_OPTIONAL(opt) requires requires { opt; } || true

namespace benchpp {

/**@brief an efficient way to store values at different points in a single run
 * and over multiple runs,
 * for the T template value, make a struct of all things being measured at each point,
 * if measuring all the same things at that point
 * it puts everything together such that push_back is as fast as possible, but can be reorganised
 */
template<typename T, std::size_t T_pointCount, std::size_t T_runCount>
class EventRecord {
private:
  T * m_dataPtr;
  std::size_t m_pointNum{0};
  std::size_t m_runNum{0};

public:
  [[nodiscard]] constexpr
  std::size_t 
  pointCount(void) const noexcept {
    return T_pointCount;
  }

  [[nodiscard]] constexpr
  std::size_t
  runCount(void) const noexcept {
    return T_runCount;
  }
  
  [[nodiscard]] constexpr
  std::size_t
  totalEvents(void) const noexcept {
    return pointCount() * runCount();
  }

  EventRecord(void) : m_dataPtr(new T[totalEvents()]) {}

  ~EventRecord(void) {
    delete[] m_dataPtr;
  }

  void
  push_back(const T& val) noexcept {
    m_dataPtr[m_currentIdx()] = val;
    m_pointNum++;
  };

  void
  run_complete(void) noexcept {
    assert(m_pointNum == T_pointCount);
    m_pointNum = 0;
    m_runNum++;
  };

  [[nodiscard]]
  std::span<const T>
  get_run(std::size_t runNum) const noexcept {
    return std::span<const T>{m_dataPtr + runNum * T_pointCount, T_pointCount};
  };

  [[nodiscard]]
  std::vector<const T>
  get_point(std::size_t pointNum) const {
    std::vector<T> points;
    points.reserve(runCount());

    for (std::size_t i = 0; i < T_runCount; i++) {
      points.push_back(m_dataPtr[pointNum + i * T_pointCount]);
    }

    return points;
  };

  [[nodiscard]]
  std::size_t
  currentPointNum(void) const noexcept {
    return m_pointNum;
  }

  [[nodiscard]]
  std::size_t
  currentRunNum(void) const noexcept {
    return m_runNum;
  }

private:
  [[nodiscard]]
  std::size_t
  m_currentIdx(void) {
    return m_runNum * pointCount() + m_pointNum;
  };

};

template<typename T>
concept EventCounter = requires(T counter) {
  { counter.start() } -> std::same_as<void>;
  { counter.stop() } -> std::same_as<void>;
  { counter.read() } -> std::convertible_to<std::int64_t>;
    
  BENCHPP_CONCEPT_OPTIONAL({ counter.reset() } -> std::same_as<void>);
  
  BENCHPP_CONCEPT_OPTIONAL({ counter.isRunning() } -> std::convertible_to<bool>);
};

template<EventCounter base_T, class readVal_T = std::int64_t>
class EventCounterRecorder : base_T {
private:
  std::vector<readVal_T> m_record;
};

}

#endif /* BENCHPP_EVENTS_HPP */
