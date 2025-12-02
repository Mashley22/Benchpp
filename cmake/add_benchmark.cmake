function(add_benchmark TARGET_BENCHMARK ITERATIONS)

  set_target_properties(${TARGET_BENCHMARK} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET_BENCHMARK}
  )

  target_link_libraries(${TARGET_BENCHMARK}
    PRIVATE
    benchpp
  )

endfunction()
