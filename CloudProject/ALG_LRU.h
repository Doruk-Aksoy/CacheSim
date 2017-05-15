#pragma once

#include "Algorithm.h"

class ALG_LRU : public Algorithm {

	public:

		Simulation_Result work(vector<Node*>&, uint64_t, uint64_t, uint64_t);

	private:

		void do_age_pass(vector<Data>&);
};