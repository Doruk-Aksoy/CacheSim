#pragma once

#include <random>
#include <chrono>
#include <cmath>

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

		template <typename T>
		T pick_exp(T min, T max) {
			// to do: turn to version using c++ exp dist
			double num = std::uniform_real_distribution<double>{ 0.0, 1.0 } (eng);
			while (num < 1.e-6)
				num = std::uniform_real_distribution<double>{ 0.0, 1.0 } (eng);
			T result = -((max + min) / 2.0) * log(num);
			if (result < min)
				result = min;
			if (result > max)
				result = max;
			return result;
		}

	private:        
    	std::mt19937 eng {std::random_device{}() }; // mersenne twister is default
};

// we will use this one for generating, it's global
extern RNG rgen;