#ifndef BENCHPP_TIMER_HPP
#define BENCHPP_TIMER_HPP

#include <chrono>
#include <vector>
#include <array>

#include <Bench++/assert.hpp>

namespace benchpp {

#ifdef BENCHPP_USE_HIGH_RESOLUTION_CLOCK
using Clock_t = std::chrono::high_resolution_clock;
#else
using Clock_t = std::chrono::steady_clock;
#endif

using TimePoint_t = std::chrono::time_point<Clock_t>;
using Time_t = std::chrono::nanoseconds;
using Count_t = Time_t::rep;


// DONT TRY TO USE THIS WITH THE STATS STUFF
class BasicTimer {
public:

  void 
  start(void) noexcept;

  void
  stop(void) noexcept;
  
  Time_t
  duration(void) const noexcept;
  
  void
  reset(void) noexcept;

private:
  TimePoint_t m_startTime{};
  Time_t m_recordedTime{0};
  bool m_running{false};
};

/**@brief For collecting several times, either in one run or over many runs, but not both
 */
class Timer : public BasicTimer {
public:

  void
  record(void) noexcept;

  void
  recordAndReset(void) noexcept;
  
  [[nodiscard]]
  std::span<const Count_t>
  times(void) const noexcept;
    
  /**@brief empties the internal timer
   * @retval the currently stored times
   */
  [[nodiscard]]
  std::vector<Count_t>
  emptyTimes(void);

private:
  std::vector<Count_t> m_times;
  BasicTimer m_stopwatch;
};


/**@brief a class for being able to collect many times in one run and do several runs
 */
template<std::size_t pointCount>
class MultiPointTimer {
private:
  std::size_t m_curPointCount = 0;
  std::array<std::vector<Count_t>, pointCount> m_times;
  BasicTimer m_stopwatch;

public:

  /**@brief for starting a new run
   */
  void
  start(void) noexcept {
    ASSERT(m_curPointCount == 0);
    m_stopwatch.start();
  }
  
  /**@brief for pausing mid run
   */
  void 
  pause(void) noexcept {
    m_stopwatch.stop();
  }

  void 
  lap(void) noexcept {
    ASSERT(m_curPointCount < pointCount);
    m_times[m_curPointCount++].push_back(m_stopwatch.duration());
    m_stopwatch.reset();
    m_stopwatch.start();
  }
  
  void
  endRun(void) noexcept {
    m_curPointCount = 0;
    m_stopwatch.reset();
  }


};

}

#endif /* BENCHPP_TIMER_HPP */
