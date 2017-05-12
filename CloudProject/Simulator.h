#ifndef SIMULATOR_IN
#define SIMULATOR_IN

#include <string>

#include "Global.h"
#include "Algorithm.h"
#include "RNG.h"
#include "Node.h"

using std::string;

enum sim_t {
	SIM_FIFO,
	SIM_LRU,
	SIM_LVF,
	SIM_SKF
};

class Simulator {
	
	public:
		
		Simulator(sim_t s) : st(s), rgen(std::chrono::high_resolution_clock::now().time_since_epoch().count()) { }
		
		uint64_t get_frame() {
			return frame;
		}
		
		void set_frame(int f) {
			frame = f;
		}
		
		RNG& get_rng() {
			return rgen;
		}
		
		void run(int, int);
		void read_data(const string&);
		
	private:
		
		uint64_t		frame;				// Current time frame of the simulation
		sim_t			st;					// Simulation type (Algorithm)
		RNG				rgen;				// Random Number Generator
		vector<Node>	nodes;				// Nodes to run the simulation on
	
};

#endif
