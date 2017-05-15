#pragma once

#include "Simulator.h"
#include "Simulation_Result.h"
#include "Node.h"

class Algorithm {
	
	public:

		Algorithm() : sim_delay(0), data_pos(0) { }

		// find data in a given network of nodes
		Node* find_data(vector<Node*>& nodes, uint64_t data_id) {
			sim_delay = 0;
			for (Node* N : nodes) {
				data_pos = 0;
				vector<Data> data_list = N->get_allData();
				for (Data& D : data_list)
					if (data_id == D.get_id())
						return N;
					else {
						sim_delay += D.get_delay();
						data_pos++;
					}
			}
			return nullptr;
		}

		bool find_data(vector<Data>& cache, uint64_t id) {
			cache_delay = 0;
			data_pos = 0;
			for (Data& D : cache)
				if (D.get_id() == id)
					return true;
				else {
					cache_delay += CACHE_DATA_ACCESS_DELAY;
					data_pos++;
				}
				return false;
		}

		uint64_t get_sim_delay() const {
			return sim_delay;
		}

		uint64_t get_data_pos() const {
			return data_pos;
		}

		virtual Simulation_Result work(vector<Node*>&, uint64_t, uint64_t, uint64_t) = 0;
		
	protected:
		
		uint64_t		sim_delay;
		uint64_t		data_pos;
		uint64_t		cache_delay;

};