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
int64 DATA_DELAY_MAX;
int64 TESTFILECOUNT;

int64 WEIGHT_PERIODIC;
int64 WEIGHT_ONDEMAND;
int64 WEIGHT_EMERGENCY;
#define TOTAL_TYPE_WEIGHT WEIGHT_PERIODIC + WEIGHT_ONDEMAND + WEIGHT_EMERGENCY

enum {
	GET_TYPE,
	GET_META
};

enum meta_value {
	META_BIN,
	META_TXT,
	META_IMAGE,
	META_SOUND,
	META_VIDEO
};

int64 WEIGHT_META_BIN;
int64 WEIGHT_META_TXT;
int64 WEIGHT_META_IMAGE;
int64 WEIGHT_META_SOUND;
int64 WEIGHT_META_VIDEO;
#define TOTAL_META_WEIGHT WEIGHT_META_BIN + WEIGHT_META_TXT + WEIGHT_META_IMAGE + WEIGHT_META_SOUND + WEIGHT_META_VIDEO

const char* data_type_labels[3] = { "Periodic", "On Demand", "Emergency" };
const vector<int64*> data_type_weights = { &WEIGHT_PERIODIC, &WEIGHT_ONDEMAND, &WEIGHT_EMERGENCY };
const vector<int64*> data_meta_weights = { &WEIGHT_META_BIN, &WEIGHT_META_TXT, &WEIGHT_META_IMAGE, &WEIGHT_META_SOUND, &WEIGHT_META_VIDEO };

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
			DATA_DELAY_MAX = atoi(&(*it)[equal_pos]);
		else if(line_count == 5)
			TESTFILECOUNT = atoi(&(*it)[equal_pos]);
		else if(line_count == 6)
			WEIGHT_PERIODIC = atoi(&(*it)[equal_pos]);
		else if(line_count == 7)
			WEIGHT_ONDEMAND = atoi(&(*it)[equal_pos]);
		else if(line_count == 8)
			WEIGHT_EMERGENCY = atoi(&(*it)[equal_pos]);
		else if(line_count == 9)
			WEIGHT_META_BIN = atoi(&(*it)[equal_pos]);
		else if(line_count == 10)
			WEIGHT_META_TXT = atoi(&(*it)[equal_pos]);
		else if(line_count == 11)
			WEIGHT_META_IMAGE = atoi(&(*it)[equal_pos]);
		else if(line_count == 12)
			WEIGHT_META_SOUND = atoi(&(*it)[equal_pos]);
		else if(line_count == 13)
			WEIGHT_META_VIDEO = atoi(&(*it)[equal_pos]);
		++line_count;
	}
	// set weights to minimum 1
	if(!WEIGHT_PERIODIC)
		WEIGHT_PERIODIC = 1;
	if(!WEIGHT_ONDEMAND)
		WEIGHT_ONDEMAND = 1;
	if(!WEIGHT_EMERGENCY)
		WEIGHT_EMERGENCY = 1;
	if(!WEIGHT_META_BIN)
		WEIGHT_META_BIN = 1;
	if(!WEIGHT_META_TXT)
		WEIGHT_META_TXT = 1;
	if(!WEIGHT_META_IMAGE)
		WEIGHT_META_IMAGE = 1;
	if(!WEIGHT_META_SOUND)
		WEIGHT_META_SOUND = 1;
	if(!WEIGHT_META_VIDEO)
		WEIGHT_META_VIDEO = 1;
		
	cout << "Loaded settings:\n\tNODES = " << NODES << "\n\tDATA PER NODE = " << DATA_PER_NODE << "\n\tDATA_SIZE_MIN = " << DATA_SIZE_MIN;
	cout << "\n\tDATA_SIZE_MAX = " << DATA_SIZE_MAX << "\n\tDATA_DELAY_MAX = " << DATA_DELAY_MAX << "\n\tTESTFILECOUNT = " << TESTFILECOUNT;
	cout << "\n\tWEIGHT_PERIODIC = " << WEIGHT_PERIODIC << "\n\tWEIGHT_ONDEMAND = " << WEIGHT_PERIODIC << "\n\tWEIGHT_EMERGENCY " << WEIGHT_PERIODIC;
	cout << "\n\tWEIGHT_META_BIN = " << WEIGHT_META_BIN << "\n\tWEIGHT_META_TXT = " << WEIGHT_META_TXT << "\n\tWEIGHT_META_IMAGE = " << WEIGHT_META_IMAGE;
	cout << "\n\tWEIGHT_META_SOUND = " << WEIGHT_META_SOUND << "\n\tWEIGHT_META_VIDEO = " << WEIGHT_META_VIDEO;  
}

size_t weighted_type_pick(int option) {
	bool picked = false;
	int64 weight = 0, choice = 0;
	const vector<int64*>* data_weights;
	int64 TOTAL_WEIGHT;
	switch(option) {
		case GET_TYPE:
			TOTAL_WEIGHT = TOTAL_TYPE_WEIGHT;
			data_weights = &data_type_weights;
		break;
		default:
			TOTAL_WEIGHT = TOTAL_META_WEIGHT;
			data_weights = &data_meta_weights;
		break;
	}
	
	while(!picked) {
		weight = rgen.pick(1, TOTAL_WEIGHT);
		int64 wsum = 0;
		for(size_t i = 0; !picked && i < data_weights->size(); ++i) {
			wsum += *(*data_weights)[i];
			if(wsum >= weight) {
				picked = true;
				choice = i;
			}
		}
	}
	return choice;
}

void make_tests(fstream& outf) {
	int id = 1;
	
	for(int i = 0; i < NODES; ++i) {
		outf << "--- NODE " << i + 1 << " DATA ---\n";
		for(int j = 0; j < DATA_PER_NODE; ++j) {
			outf << "Node: " << id++ << '\n';
			outf << "Data size: " << rgen.pick(DATA_SIZE_MIN, DATA_SIZE_MAX) << '\n';
			outf << "Data delay max: " << rgen.pick(0, DATA_DELAY_MAX) << '\n';
			outf << "Data type: " << data_type_labels[weighted_type_pick(GET_TYPE)] << '\n';
			outf << "Data meta: " << weighted_type_pick(GET_META) << '\n';
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
	system("PAUSE");
}
