#include <algorithm>

#include "ALG_FIFO.h"

#include "RNG.h"

// delay calculation from here: http://people.kth.se/~ingo/MasterThesis/ThesisDamienGille2007.pdf

Simulation_Result ALG_FIFO::work(vector<Node*>& nodes, uint64_t cache_size, uint64_t iter, uint64_t data_count) {
	// create a queue to hold cache_size many elements
	vector<Data> cache;
	uint64_t total_delay = 0, hit_count = 0, miss_count = 0, total_cache_delay = 0;
	vector<Data>& data_list = nodes[0]->get_allData();
	Node* N = nullptr;
	for (uint64_t i = 0; i < iter; ++i) {
		// we will pick data and put them into cache
		uint64_t data_id = rgen.pick(1, data_count);
		// put the data in the cache if not full
		if (cache.size() < cache_size) {
			// check if it's cached already
			if (find_data(cache, data_id)) {
				hit_count++;
				total_cache_delay += cache_delay;
			}
			else {
				// find which node has this data
				N = find_data(nodes, data_id);
				// cache it
				cache.push_back(N->get_allData()[data_pos]);
				miss_count++;
				total_delay += sim_delay;
			}
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
	return Simulation_Result(hit_count, miss_count, total_delay, total_cache_delay, iter);
}