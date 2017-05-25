#ifndef GLOBAL_IN
#define GLOBAL_IN

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <string>
#include <sstream>

#define MAX_ALGORITHMS 3
#define MAX_PARAMS 5
#define CACHE_DATA_ACCESS_DELAY 5 // 5 ns assumed
#define DELAY_CONVERT_RATIO 1000.0 // from ms to us
#define CACHE_CONVERT_RATIO 1000000.0 // from ns to ms

#define WEIGHT_AGEFREQ_RATIO 500.0
#define WEIGHT_METATYPE_RATIO 500.0 / 12.0

using std::cout;
using std::cin;
using std::fstream;
using std::string;
using std::stringstream;
using std::vector;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;

#endif
