add_executable(post_vs_pre_increment
  integer.cpp
  vector.cpp
)

add_executable(post_vs_pre_increment_optimised
  integer.cpp
  vector.cpp
)

target_compile_options(post_vs_pre_increment_optimised
  PRIVATE
    "-O2"
)

add_sample(post_vs_pre_increment)
add_sample(post_vs_pre_increment_optimised)
