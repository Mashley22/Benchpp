function(add_sample TARGET_NAME ITERATIONS)

  target_link_libraries(${TARGET_NAME}
    PRIVATE
      benchpp
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
  
  set_target_properties(${TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )

  add_benchmark(TARGET_NAME ITERATIONS)

endfunction()

add_subdirectory(simple)
