# Benchpp 🚀

A **lightweight C++20 benchmarking and performance monitoring framework** with built-in support for system metrics like cache misses, CPU instructions, memory usage, and more.

## Features ✨

- **C++20 Modern Features**: Uses C++20 modules and modern C++ practices
- **Comprehensive Metrics**: Tracks execution time, CPU cycles, cache misses, branch misses, page faults, and more
- **Organized Benchmarks**: Group benchmarks by category for better organization
- **Flexible Iteration Control**: Set custom iteration counts for long-running benchmarks
- **CLI Interface**: Run specific benchmarks, groups, or all at once with intuitive commands
- **Minimal Overhead**: Lightweight design with zero-cost abstractions
- **Cross-Platform**: Linux support with extensible architecture

## Requirements

- **C++20 or higher** (standard requirement)
- **CMake 3.28+**
- **Catch2** (for testing)

### Build Options
- `BENCHPP_DEBUG` (ON/OFF) - Enable debugging and asserts
- `BENCHPP_TEST` (ON/OFF) - Build unit tests
- `BENCHPP_SAMPLES` (ON/OFF) - Build sample benchmarks
- `BENCHPP_USE_HIGH_RESOLUTION_CLOCK` (ON/OFF) - Use high-resolution clock instead of steady clock

## Building and Usage
- Add as subdirectory usage the benchpp_add_core_library cmake function to create a cmake target library with everything you need
- bash scripts are provided in the build/validation and build/samples directories to build the unit tests or the samples

## Quick Start

### 1. Define a Benchmark

Create a simple benchmark by defining a function and registering it, optionally register a timer and it will automatically print out the
statistical information if the benchmark has run

```cpp
#include <cstddef>
#include <atomic>

#include <Bench++/macros.hpp>

import Benchpp;

#include <Bench++/samples/utils.hpp>

#define RUN_NUM 100
#define LOOP_NUM std::size_t(1e6)

namespace benchpp {

namespace {

Timer M_timer;

BENCHPP_BENCHMARK_FUNC
void
M_pushBack(void) {
  std::vector<int> vec;
  M_timer.start();
  for (std::size_t i = 0; i < LOOP_NUM; i++) {
    vec.push_back(i);
  }
  M_timer.stop();
  M_timer.recordAndReset();
  (void)vec;
}

}

}

namespace {

benchpp::BenchmarkInfo vectorPushBack = {
  .name = "vector push back",
  .group = "containers",
  .function = benchpp::M_pushBack,
  .runNum = RUN_NUM,
  .p_timer = &benchpp::M_timer
};

}

REGISTER_BENCHMARK(vectorPushBack);
```

## Architecture

### Core Components

- **Registry** (`src/registry.cpp`, `modules/private/registry.cppm`)
  - Manages benchmark registration and execution
  - Handles grouping and iteration control

- **CLI** (`src/cli.cpp`, `modules/public/cli.cppm`)
  - Command-line argument parsing
  - Supports multiple benchmark/group selection

- **Timer** (`src/timer.cpp`)
  - Precise timing measurements using `std::chrono`
  - Configurable clock type (steady vs high-resolution)

- **Metrics** (`src/core_metrics/`, `src/linux/`, `src/cache/`)
  - Cache performance metrics (misses, hits)
  - CPU-level metrics (cycles, instructions)
  - Memory tracking (page faults, context switches)

### Module Structure

```
benchpp (Main Module)
├── :registry        - Benchmark registration and execution
├── :cli            - Command-line interface
├── :timer          - High-precision timing
├── :metrics        - Performance metrics collection
├── :stats          - Statistical analysis
└── :utils          - Utility functions
```
## License

See [LICENSE](LICENSE) file for details.

## Acknowledgments

- Uses [Catch2](https://github.com/catchorg/Catch2) for testing
