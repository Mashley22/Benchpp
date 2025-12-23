function(add_post_vs_pre_increment_sample TARGET_NAME)

  add_sample(${TARGET_NAME})

  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/post_vs_pre_increment/
  )

endfunction()

add_executable(basic
  integer.cpp
  vector.cpp
)

add_executable(optimised
  integer.cpp
  vector.cpp
)

target_compile_options(optimised
  PRIVATE
    "-O2"
)

add_post_vs_pre_increment_sample(basic)
add_post_vs_pre_increment_sample(optimised)
