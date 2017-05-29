#include "Simulation_Result.h"

vector<uint64_t> Simulation_Result::total_hit_count(MAX_ALGORITHMS);
vector<uint64_t> Simulation_Result::total_miss_count(MAX_ALGORITHMS);
vector<double> Simulation_Result::total_hit_ratio(MAX_ALGORITHMS);
vector<double> Simulation_Result::total_miss_ratio(MAX_ALGORITHMS);
vector<double> Simulation_Result::total_time_to_hit(MAX_ALGORITHMS);
vector<double> Simulation_Result::total_avg_cache_access_delay(MAX_ALGORITHMS);