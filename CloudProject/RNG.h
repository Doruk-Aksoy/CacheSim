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

		template <typename T>
		T pick(T min, T max) {
		    return std::uniform_int_distribution<T> {min, max} (eng); // uniformly distribute numbers in range, use mersenne twister to pick
		}

	private:        
    	std::mt19937 eng {std::random_device{}() }; // mersenne twister is default
};

// we will use this one for generating, it's global
extern RNG rgen;

#endif
