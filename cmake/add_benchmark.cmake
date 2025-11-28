function(add_benchmark TARGET_BENCHMARK ITERATIONS)

  set_target_properties(${TARGET_BENCHMARK} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET_BENCHMARK}
  )
  
  set(LAUNCHER "launcher_${TARGET_BENCHMARK}")

  add_executable(${LAUNCHER}
    ${BENCHPP_ROOT_DIR}/src/launcher/launcher_main.cpp
  )

  set_target_properties(${LAUNCHER} {PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET_BENCHMARK}
  )

  target_compile_definitions(${LAUNCHER} PRIVATE 
    BENCHMARK_NAME = "./${TARGET_BENCHMARK}"
    ITERATION_NUM = ${ITERATIONS}
  )

  target_link_libraries(${TARGET_BENCHMARK}
    PRIVATE
    benchpp
  )

endfunction()
