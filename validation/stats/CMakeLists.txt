add_executable(test_stats
  test_range.cpp
  test_median.cpp
  test_generate.cpp
)

target_link_libraries(test_stats 
  PRIVATE
    benchpp
    Catch2::Catch2WithMain
  )

catch_discover_tests(test_stats)
