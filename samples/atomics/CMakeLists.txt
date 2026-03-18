function(add_atomics_sample TARGET_NAME)

  add_sample(${TARGET_NAME})

  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/atomics/
  )

endfunction()

add_executable(atomic
  load.cpp
  increment.cpp
)

add_executable(atomic_optimised
  load.cpp
  increment.cpp
)

target_compile_options(atomic_optimised
  PRIVATE
    "-O3"
)

add_atomics_sample(atomic)
add_atomics_sample(atomic_optimised)
