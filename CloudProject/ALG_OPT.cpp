#include <algorithm>

#include "ALG_OPT.h"

#include "RNG.h"

Simulation_Result ALG_OPT::work(vector<Node*>& nodes, uint64_t cache_size, uint64_t iter, const vector<uint64_t>& dseq) {
	// create a queue to hold cache_size many elements
	vector<Data> cache;
	uint64_t total_delay = 0, hit_count = 0, miss_count = 0, total_cache_delay = 0;
	Node* N = nullptr;
	for (uint64_t i = 0; i < iter; ++i) {
		// we will pick data and put them into cache
		uint64_t data_id = dseq[i];
		// do we have this on cache?
		if (find_data(cache, data_id)) {
			hit_count++;
			total_cache_delay += cache_delay;
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
				auto it = cache.begin();
				if (i < iter - 4) {
					// turns out it's not, but erase data that we won't need in the future
					for (; it != cache.end() && it->get_id() == dseq[i] || it->get_id() == dseq[i + 1] || it->get_id() == dseq[i + 2] || it->get_id() == dseq[i + 3]; ++it);
				}
				cache.erase(it);
				N = find_data(nodes, data_id);
				// cache the new element in it's place
				cache.push_back(N->get_allData()[data_pos]);
				miss_count++;
				total_delay += sim_delay;
			}
		}
	}
	return Simulation_Result(hit_count, miss_count, total_delay, total_cache_delay, iter);
}