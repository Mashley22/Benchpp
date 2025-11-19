#include <Bench++/timer.hpp>

#include <Bench++/assert.hpp>
#include <Bench++/assert.hpp>

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
}

Time_t 
BasicTimer::duration(void) const noexcept {
  if (m_running) {
    return m_recordedTime +
          std::chrono::duration_cast<Time_t>(Clock_t::now() - m_startTime);
  }
  else {
    return m_recordedTime;
  }
}

void
BasicTimer::reset(void) noexcept {
  ASSERT(m_running == false);
  m_running = false;
  m_recordedTime = Time_t(0);
}

void
Timer::record(void) noexcept {
  m_times.push_back(BasicTimer::duration().count());
}

void
Timer::recordAndReset(void) noexcept {
  record();
  BasicTimer::reset();
}

std::span<const Count_t>
Timer::times(void) const noexcept {
  return m_times;
}

}
