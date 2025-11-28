#include <cstdlib>
#include <iostream>

#ifndef BENCHMARK_EXE
#define BENCHMARK_EXE "markbench"
#endif

#ifndef ITERATION_NUM
#define ITERATION_NUM 1
#endif 

namespace {

void
M_doIterations(std::size_t iterationNum) {
  for (std::size_t i = 1; i <= iterationNum; i++) {
    std::cout << "Beginning iteration: " << i << '\n';
    std::system(BENCHMARK_EXE);
    std::cout << "Finished iteration: " << i << '\n';
  }
}

}

int main(int argc, char** argv) {
  if (argc == 1) {
    M_doIterations(ITERATION_NUM);
  }
  if (argc == 2) {
    M_doIterations(std::stoi(argv[1]));
  }
}
