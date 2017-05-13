#pragma once

#include "Simulator.h"
#include "Node.h"

class Algorithm {
	
	public:

		virtual void work(vector<Node*>&) = 0;
		
};