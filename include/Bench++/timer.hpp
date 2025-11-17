#ifndef BENCHPP_TIMER_HPP
#define BENCHPP_TIMER_HPP

#include <chrono>

namespace bpp {

class BasicTimer {
public:

#ifdef BENCHPP_USE_HIGH_RESOLUTION
using Clock_t = std::chrono::high_resolution_clock;
#else
using Clock_t = std::chrono::steady_clock;
#endif

using TimePoint_t = std::chrono::time_point<Clock_t>;

  void start(void) noexcept;



private:
  TimePoint_t m_startTime{};
  TimePoint_t m_endTime{};

};

}

#endif /* BENCHPP_TIMER_HPP */
