#ifndef BENCHPP_SAMPLES_UTILS_HPP
#define BENCHPP_SAMPLES_UTILS_HPP

#include <new>

#define ATTRIB_CACHE_LINE_ALIGN __attribute__((aligned(std::hardware_destructive_interference_size)))

#endif /* BENCHPP_SAMPLES_UTILS */
