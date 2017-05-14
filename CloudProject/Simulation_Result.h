#pragma once

class Simulation_Result {

	public:

		Simulation_Result(uint64_t hit_count, uint64_t miss_count, uint64_t total_delay, uint64_t total_cache_delay, uint64_t iter) {
			hit_ratio = 100 * static_cast<double>(hit_count) / iter;
			miss_ratio = 100 * static_cast<double>(miss_count) / iter;
			total_cache_access_delay = total_cache_delay / CACHE_CONVERT_RATIO; // we assume cache speed in ns, convert to ms
			time_to_hit = total_cache_delay + static_cast<double>(total_delay) / DELAY_CONVERT_RATIO; // we assumed us here, convert to ms
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

	private:

		double			hit_ratio;
		double			miss_ratio;
		double			time_to_hit;
		double			total_cache_access_delay;
};