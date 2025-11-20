set(TEST_TIMER_SOURCES  
  test_BasicTimer.cpp
  test_Timer.cpp
  test_MultiPointTimer.cpp
)

add_executable(test_steady_timer
  ${TEST_TIMER_SOURCES}
)

add_unit_test(test_steady_timer)

add_executable(test_highres_timer
  ${TEST_TIMER_SOURCES}
)

target_compile_definitions(test_highres_timer
  PRIVATE
  BENCHPP_USE_HIGH_RESOLUTION_CLOCK
)

add_unit_test(test_highres_timer)
