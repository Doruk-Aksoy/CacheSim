#pragma once

#include "Algorithm.h"
#include "ALG_FIFO.h"
#include "ALG_LRU.h"
#include "ALG_SKF.h"

class Algorithm_Factory {

	public:

		static Algorithm* get_algorithm(sim_t s) {
			if (s == SIM_FIFO)
				return new ALG_FIFO();
			else if (s == SIM_LRU)
				return new ALG_LRU();
			else
				return new ALG_SKF();
		}

};