#pragma once

#include "Global.h"
#include "Algorithm.h"
#include "RNG.h"
#include "Node.h"
#include "Simulation_Result.h"

enum sim_t {
	SIM_FIFO,
	SIM_LRU,
	SIM_SKF,
	SIM_OPT
};

extern const char* simulation_label[SIM_OPT + 1];

class Simulator {
	
	public:
		
		Simulator(sim_t s, uint64_t i, uint64_t c) : st(s), iter(i), cache_size(c), data_count(0) { }
		~Simulator();
		
		uint64_t get_frame() {
			return frame;
		}
		
		void set_frame(int f) {
			frame = f;
		}
		
		void run(int, const vector<vector<uint64_t>>&);						// Runs the simulation on given file #
		void dump_nodes();													// Debug
		void read_data(const string&);										// Reads data from file
		void report_result(const Simulation_Result& ,int, size_t);			// Dumps output file
		static void populate(vector<uint64_t>& d, uint64_t, uint64_t);		// populates a given vector
		
	private:
		
		uint64_t			frame;											// Current time frame of the simulation
		uint64_t			iter;											// Iteration count
		uint64_t			cache_size;										// Size of the cache
		sim_t				st;												// Simulation type (Algorithm)
		vector<Node*>		nodes;											// Nodes to run the simulation on

		uint64_t			data_count;										// Total count of data in all nodes

};