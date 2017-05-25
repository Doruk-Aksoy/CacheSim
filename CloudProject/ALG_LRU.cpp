#include "ALG_LRU.h"

#include <algorithm>

Simulation_Result ALG_LRU::work(vector<Node*>& nodes, uint64_t cache_size, uint64_t iter, const vector<uint64_t>& dseq) {
	// create a queue to hold cache_size many elements
	vector<Data> cache;
	uint64_t total_delay = 0, hit_count = 0, miss_count = 0, total_cache_delay = 0;
	Node* N = nullptr;
	for (uint64_t i = 0; i < iter; ++i) {
		// do we have this on cache?
		uint64_t data_id = dseq[i];
		if (find_data(cache, data_id)) {
			hit_count++;
			total_cache_delay += cache_delay;
			cache[data_pos].set_age(0); // used, set age to 0
		}
		else {
			if (cache.size() < cache_size) {
				// find which node has this data
				N = find_data(nodes, data_id);
				// cache it
				cache.push_back(N->get_allData()[data_pos]);
				miss_count++;
				total_delay += sim_delay;
			}
			else {
				// remove the first in queue
				cache.erase(cache.begin());
				N = find_data(nodes, data_id);
				// cache the new element in it's place
				cache.push_back(N->get_allData()[data_pos]);
				miss_count++;
				total_delay += sim_delay;
			}
		}
		// make data in cache get older each iteration
		do_age_pass(cache);
		std::sort(cache.begin(), cache.end(), data_age_compare());
	}
	return Simulation_Result(hit_count, miss_count, total_delay, total_cache_delay, iter);
}