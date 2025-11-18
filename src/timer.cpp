#include <Bench++/timer.hpp>

namespace benchpp {

void
BasicTimer::start(void) noexcept {
  ASSERT(m_running == false);
  m_running = true;

  m_startTime = Clock_t::now();
}

void 
BasicTimer::stop(void) noexcept {
  ASSERT(m_running == true);
  m_running = false;

  m_recordedTime +=
    std::chrono::duration_cast<Time_t>(Clock_t::now() - m_startTime);
  
  m_startTime = Clock_t::now();
}

Time_t 
BasicTimer::duration(void) const noexcept {
  if (m_running == true) {
    return m_recordedTime;
  }
  else {
    return m_recordedTime +
          std::chrono::duration_cast<Time_t>(Clock_t::now() - m_startTime);
  }
}

void
BasicTimer::reset(void) noexcept {
  ASSERT(m_running == false);
  m_running = false;
  m_recordedTime = Time_t(0);
}

void
Timer::start(void) noexcept {
  m_stopwatch.start();
}

void
Timer::stop(void) noexcept {
  m_stopwatch.stop();
}

void
Timer::reset(void) noexcept {
  m_stopwatch.reset();
}

void
Timer::record(void) noexcept {
  m_times.push_back(m_stopwatch.duration().count());
}

void
Timer::recordAndReset(void) noexcept {
  record();
  reset();
}

std::span<const Count_t>
Timer::times(void) const noexcept {
  return m_times;
}

}
