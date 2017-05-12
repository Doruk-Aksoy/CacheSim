#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <string>
#include <utility>
#include <iostream>
#include <cstring>

#include "RNG.h"

using std::vector;
using std::deque;
using std::set;
using std::pair;
using std::fstream;
using std::stringstream;
using std::string;
using std::cout;

int64 NODES;
int64 DATA_PER_NODE;
int64 DATA_SIZE_MIN;
int64 DATA_SIZE_MAX;
int64 DATA_AGE_MIN;
int64 DATA_AGE_MAX;
int64 DATA_DELAY_MAX;
int64 TESTFILECOUNT;

enum meta_value {
	META_BIN,
	META_TXT,
	META_IMAGE,
	META_SOUND,
	META_VIDEO
};

const char* data_type_labels[3] = { "Periodic", "On Demand", "Emergency" };

void read_settings() {
	fstream settings("test_gen_settings.txt", std::ios::in);
	string line;
	vector<string> data;
	// while I can read, do read
	while (std::getline(settings, line)) {
		if (*line.begin() == '#')
			continue;
		data.push_back(line);
	}
	// line 1 =TEST_MIN, line 2 = TEST_MAX, line 3 = WEIGHT_MIN, line 4 = WEIGHT_MAX, line 5 = MINVERTEX, line 6 = MAXVERTEX and line 7 = TEST FILE COUNT
	// line 8 = SPARSITY
	size_t line_count = 0;
	for(auto it = data.begin(); it != data.end(); ++it) {
		size_t equal_pos = 1 + it->find_first_of('=');
		if(!line_count)
			NODES = atoi(&(*it)[equal_pos]);
		else if(line_count == 1)
			DATA_PER_NODE = atoi(&(*it)[equal_pos]);
		else if(line_count == 2)
			DATA_SIZE_MIN = atoi(&(*it)[equal_pos]);
		else if(line_count == 3)
			DATA_SIZE_MAX = atoi(&(*it)[equal_pos]);
		else if(line_count == 4)
			DATA_AGE_MIN = atoi(&(*it)[equal_pos]);
		else if(line_count == 5)
			DATA_AGE_MAX = atoi(&(*it)[equal_pos]);
		else if(line_count == 6)
			DATA_DELAY_MAX = atoi(&(*it)[equal_pos]);
		else if(line_count == 7)
			TESTFILECOUNT = atoi(&(*it)[equal_pos]);
		++line_count;
	}
	cout << "Loaded settings:\n\tNODES = " << NODES << "\n\tDATA PER NODE = " << DATA_PER_NODE << "\n\tDATA_SIZE_MIN = " << DATA_SIZE_MIN;
	cout << "\n\tDATA_SIZE_MAX = " << DATA_SIZE_MAX << "\n\tDATA_AGE_MIN = " << DATA_AGE_MIN << "\n\tDATA_AGE_MAX = " << DATA_AGE_MAX;
	cout << "\n\tDATA_DELAY_MAX = " << DATA_DELAY_MAX << "\n\tTESTFILECOUNT = " << TESTFILECOUNT;
}

void make_tests(fstream& outf) {
	for(int i = 0; i < NODES; ++i) {
		outf << "--- NODE " << i + 1 << " DATA ---\n";
		for(int j = 0; j < DATA_PER_NODE; ++j) {
			outf << "Node: " << j + 1 << '\n';
			outf << "Data size: " << rgen.pick(DATA_SIZE_MIN, DATA_SIZE_MAX) << '\n';
			outf << "Data age: " << rgen.pick(DATA_AGE_MIN, DATA_AGE_MAX) << '\n';
			outf << "Data delay max: " << rgen.pick(0, DATA_DELAY_MAX) << '\n';
			outf << "Data type: " << data_type_labels[rgen.pick(0, 2)] << '\n';
			outf << "Data meta: " << rgen.pick(META_BIN, META_VIDEO) << '\n';
		}
	}
}

int main() {
	read_settings();
	for(int i = 0; i < TESTFILECOUNT; ++i) {
		stringstream temp;
		temp << "test_" << i + 1 << ".txt";
		fstream outf(temp.str(), std::ios::out);
		make_tests(outf);
		outf.close();
	}
	cout << "\nTest generation completed.\n";
}
