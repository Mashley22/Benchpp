module;

#include <concepts>
#include <cstdint>
#include <vector>
#include <cassert>
#include <span>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

export module Benchpp:events;
import :iteration_counter;

#define BENCHPP_CONCEPT_OPTIONAL(opt) requires requires { opt; } || true
#define BENCHPP_SAVEDATA_FOLDER "savedata/"

export namespace benchpp {

template<typename T>
concept EventsCounter = requires(T counter) {
  { counter.start() } -> std::same_as<void>;
  { counter.stop() } -> std::same_as<void>;
  { counter.read() } -> std::convertible_to<std::int64_t>;
  { counter.isRunning() } -> std::convertible_to<bool>;
    
  BENCHPP_CONCEPT_OPTIONAL({ counter.reset() } -> std::same_as<void>);
};

template<typename T>
void
saveData(T * p_data, std::size_t pointCount, std::size_t runCount) {
  std::stringstream ss;
  ss << BENCHPP_SAVEDATA_FOLDER << std::to_string(currentIteration())
     << sizeof(T) << "_" << pointCount << "_" << runCount;

  std::ofstream saveDataFile(ss.str());
  
  for (std::size_t i = 0; i < pointCount * runCount; i++) {
    saveDataFile << p_data[i];
  }
}

/**@brief an efficient way to store values at different points in a single run
 * and over multiple runs,
 * for the T template value, make a struct of all things being measured at each point,
 * if measuring all the same things at that point
 * it puts everything together such that push_back is as fast as possible, but can be reorganised
 * can also make T such that it automatically constructs and reads the values
 */
template<typename T, std::size_t T_pointCount, std::size_t T_runCount>
class EventsRecord {
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

  EventsRecord(void) : m_dataPtr(new T[totalEvents()]) {}

  ~EventsRecord(void) {
    delete[] m_dataPtr;
  }

  void
  push_back(const T& val) noexcept {
    m_dataPtr[m_currentIdx()] = val;
    m_pointNum++;
  };

  void
  record(void) noexcept {
    m_dataPtr[m_currentIdx()] = T();
    m_pointNum++;
  }

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
  std::vector<T>
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
  
  /**@note Do not bind this what or in a destructor of a static variable because of the GSIOF
   *       Make sure all calls in tis function run in main
   */
  void
  saveData(void) const {
    saveData(m_dataPtr, T_pointCount, T_runCount);
  }

private:
  [[nodiscard]]
  std::size_t
  m_currentIdx(void) {
    return m_runNum * pointCount() + m_pointNum;
  };

};

}
