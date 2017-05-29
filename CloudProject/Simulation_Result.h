#pragma once

#include "Global.h"

class Simulation_Result {

	public:

		Simulation_Result(uint64_t hit_count, uint64_t miss_count, uint64_t total_delay, uint64_t total_cache_delay, uint64_t iter) {
			this->hit_count = hit_count;
			this->miss_count = miss_count;
			hit_ratio = 100 * static_cast<double>(hit_count) / iter;
			miss_ratio = 100 * static_cast<double>(miss_count) / iter;
			total_cache_access_delay = total_cache_delay / CACHE_CONVERT_RATIO; // we assume cache speed in ns, convert to ms
			time_to_hit = total_cache_delay + static_cast<double>(total_delay) / DELAY_CONVERT_RATIO; // we assumed us here, convert to ms
		}

		uint64_t get_hit_count() const {
			return hit_count;
		}

		uint64_t get_miss_count() const {
			return miss_count;
		}

		double get_hit_ratio() const {
			return hit_ratio;
		}

		double get_miss_ratio() const {
			return miss_ratio;
		}

		double get_time_to_hit() const {
			return time_to_hit;
		}

		double get_total_cache_access_delay() const {
			return total_cache_access_delay;
		}

		void accumulate(sim_t st) {
			size_t index = static_cast<size_t>(st);
			total_hit_count[index] += hit_count;
			total_miss_count[index] += miss_count;
			total_hit_ratio[index] += hit_ratio;
			total_miss_ratio[index] += miss_ratio;
			total_avg_cache_access_delay[index] += total_cache_access_delay;
			total_time_to_hit[index] += time_to_hit;
		}

		static void reset() {
			for (size_t i = 0; i < MAX_ALGORITHMS; ++i) {
				total_hit_count[i] = 0;
				total_miss_count[i] = 0;
				total_hit_ratio[i] = 0;
				total_miss_ratio[i] = 0;
				total_time_to_hit[i] = 0;
				total_avg_cache_access_delay[i] = 0;
			}
		}

		static vector<uint64_t>		total_hit_count;
		static vector<uint64_t>		total_miss_count;
		static vector<double>		total_hit_ratio;
		static vector<double>		total_miss_ratio;
		static vector<double>		total_time_to_hit;
		static vector<double>		total_avg_cache_access_delay;

	private:

		uint64_t			hit_count;
		uint64_t			miss_count;
		double				hit_ratio;
		double				miss_ratio;
		double				time_to_hit;
		double				total_cache_access_delay;

};