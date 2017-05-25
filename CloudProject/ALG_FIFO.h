#pragma once

#include "Algorithm.h"

class ALG_FIFO : public Algorithm {

	public:

		Simulation_Result work(vector<Node*>&, uint64_t, uint64_t, const vector<uint64_t>&);
};