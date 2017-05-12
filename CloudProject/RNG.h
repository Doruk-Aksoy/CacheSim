#ifndef RNG_IN
#define RNG_IN

#include <random>
#include <chrono>

typedef long long int64; 

class RNG {
	public:
	    RNG() = default; // assign default constructor
	    ~RNG() = default;
	    RNG(std::mt19937::result_type seed) : eng(seed) {} // seed the mersenne twister engine for use
		int64 pick(int64 min, int64 max) {
		    return std::uniform_int_distribution<int64> {min, max} (eng); // uniformly distribute numbers in range, use mersenne twister to pick
		}

	private:        
    	std::mt19937 eng {std::random_device{}() }; // mersenne twister is default
};

// we will use this one for generating, it's global
const RNG rgen (std::chrono::high_resolution_clock::now().time_since_epoch().count());

#endif
