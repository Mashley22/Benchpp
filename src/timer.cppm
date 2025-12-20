module;

#include <Bench++/events.hpp>

#include <chrono>
#include <vector>

#include <cassert>

export module Benchpp:timer;

export namespace benchpp {

#ifdef BENCHPP_USE_HIGH_RESOLUTION_CLOCK
using Clock_t = std::chrono::high_resolution_clock;
#else
using Clock_t = std::chrono::steady_clock;
#endif

using TimePoint_t = std::chrono::time_point<Clock_t>;
using Time_t = std::chrono::nanoseconds;
using TimeCount_t = Time_t::rep;


// DONT TRY TO USE THIS WITH THE STATS STUFF
class BasicTimer {
public:

  void 
  start(void) noexcept;

  void
  stop(void) noexcept;
 
  [[nodiscard]]
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
  std::span<const TimeCount_t>
  times(void) const noexcept;
    
  /**@brief empties the internal timer
   * @retval the currently stored times
   */
  [[nodiscard]]
  std::vector<TimeCount_t>
  emptyTimes(void);

private:
  std::vector<TimeCount_t> m_times;
  BasicTimer m_stopwatch;
};


/**@brief a class for being able to collect many times in one run and do several runs
 */
template<std::size_t T_pointCount, std::size_t T_runCount>
class MultiPointTimer {
private:
  EventsRecord<TimeCount_t, T_pointCount, T_runCount> m_times;
  BasicTimer m_stopwatch;

public:

  /**@brief for starting a new run
   */
  void
  start(void) noexcept {
    m_stopwatch.start();
  }
  
  /**@brief for pausing mid run
   */
  void 
  stop(void) noexcept {
    m_stopwatch.stop();
  }

  void 
  lap(void) noexcept {
    m_stopwatch.stop();
    m_times.push_back(m_stopwatch.duration().count());
    m_stopwatch.reset();
    m_stopwatch.start();
  }
  
  void
  run_complete(void) noexcept {
    m_stopwatch.stop();
    m_stopwatch.reset();
    m_times.run_complete();
  }
  
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
  
  [[nodiscard]]
  auto
  get_point(std::size_t pointNum) const noexcept {
    return m_times.get_point(pointNum);
  }

  [[nodiscard]]
  auto
  get_run(std::size_t runNum) const noexcept {
    return m_times.get_run(runNum);
  }
};

}
