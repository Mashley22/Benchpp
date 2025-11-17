#ifndef BENCHPP_TIMER_HPP
#define BENCHPP_TIMER_HPP

#include <chrono>

namespace benchpp {

// DONT TRY TO USE THIS WITH THE STATS STUFF
class BasicTimer {
public:

#ifdef BENCHPP_USE_HIGH_RESOLUTION
using Clock_t = std::chrono::high_resolution_clock;
#else
using Clock_t = std::chrono::steady_clock;
#endif

using TimePoint_t = std::chrono::time_point<Clock_t>;

private:
  TimePoint_t m_startTime{};
  TimePoint_t m_endTime{};

public:

  void 
  start(void) noexcept;

  void
  stop(void) noexcept;

  template<typename Duration>
  Duration
  duration(void) const noexcept {
    return std::chrono::duration_cast<Duration>(m_startTime - m_endTime);
  }

  template<typename Duration>
  Duration
  currentElapsed(void) const noexcept {
    return std::chrono::duration_cast<Duration>(m_startTime - Clock_t::now());
  }
};

}

#endif /* BENCHPP_TIMER_HPP */
