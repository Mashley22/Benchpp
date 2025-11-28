add_executable(post_vs_pre_increment
  main.cpp
)

add_executable(post_vs_pre_increment_vector_iterators
  vector_main.cpp
)

add_benchmark(post_vs_pre_increment 1)
add_benchmark(post_vs_pre_increment_vector_iterators 1)
