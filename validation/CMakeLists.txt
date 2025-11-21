function(add_unit_test TARGET_NAME)

  target_link_libraries(${TARGET_NAME}
    PRIVATE
      benchpp
      Catch2::Catch2WithMain
    )

  target_compile_options(${TARGET_NAME}
    PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Werror
      -Wshadow
      -Wconversion
      -Wsign-conversion
  )

  target_compile_definitions(${TARGET_NAME}
    PRIVATE
      BENCHPP_TEST
  )

  catch_discover_tests(${TARGET_NAME})

endfunction()

add_subdirectory(stats)
add_subdirectory(timer)
add_subdirectory(mem)
add_subdirectory(events)
