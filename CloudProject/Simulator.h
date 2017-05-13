#pragma once

#include "Global.h"
#include "Algorithm.h"
#include "RNG.h"
#include "Node.h"

enum sim_t {
	SIM_FIFO,
	SIM_LRU,
	SIM_LVF,
	SIM_SKF
};

class Simulator {
	
	public:
		
		Simulator(sim_t s) : st(s) { }
		~Simulator();
		
		uint64_t get_frame() {
			return frame;
		}
		
		void set_frame(int f) {
			frame = f;
		}
		
		void run(int, int);
		void read_data(const string&);
		
	private:
		
		uint64_t		frame;				// Current time frame of the simulation
		sim_t			st;					// Simulation type (Algorithm)
		vector<Node*>	nodes;				// Nodes to run the simulation on
	
};