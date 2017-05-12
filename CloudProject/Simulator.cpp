#include <sstream>

#include "Simulator.h"

using std::string;
using std::stringstream;

void Simulator::read_data(const string& fname) {
	fstream input(fname, std::ios::in);
	string temp;
	while(getline(input, temp)) {
		if (temp[0] != '-') {

		}
	}
}

void Simulator::run(int begin, int end) {
	for(int i = begin; i <= end; i++) {
		stringstream temp;
		temp << "test_" << i << ".txt";
		// first read the random test data generated
		read_data(temp.str());
		// create the test objects from the data read
				
		// run simulation with specified simulation method
	}
}
