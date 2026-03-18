function(add_post_vs_pre_increment_sample TARGET_NAME)

  add_sample(${TARGET_NAME})

  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/post_vs_pre_increment/
  )

endfunction()

add_executable(post_vs_pre_increment_basic
  integer.cpp
  vector.cpp
)

add_executable(post_vs_pre_increment_optimised
  integer.cpp
  vector.cpp
)

target_compile_options(post_vs_pre_increment_optimised
  PRIVATE
    "-O3"
)

add_post_vs_pre_increment_sample(post_vs_pre_increment_basic)
add_post_vs_pre_increment_sample(post_vs_pre_increment_optimised)
