#include <sstream>

#include "Algorithm_Factory.h"
#include "Simulator.h"

const char* data_type_labels[DATA_TYPE_EMERGENCY + 1] = { "Periodic", "On Demand", "Emergency" };
const RNG rgen(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

Simulator::~Simulator() {
	for (auto n : nodes)
		delete n;
}

void Simulator::read_data(const string& fname) {
	fstream input(fname, std::ios::in);
	if (input.is_open()) {
		string temp;
		int cnt = 0, id_counter = 0;
		Node* node_temp = nullptr;
		Node** ref = nullptr;

		int id, size, age, delay, meta;
		data_type type;
		string data_t;
		// create the test objects from the data read
		while (getline(input, temp)) {
			if (temp[0] != '-') {
				/*
				Sample input
				Node: 1 -- this is the data in the BIG NODE (bad naming...)
				Data size: 31238
				Data age: 35
				Data delay max: 158
				Data type: Periodic
				Data meta: 1
				*/
				// utils
				string parse;
				stringstream ss (temp);
				if (!cnt)
					ss >> parse >> id;
				else if (cnt == 1)
					ss >> parse >> parse >> size;
				else if (cnt == 2)
					ss >> parse >> parse >> age;
				else if (cnt == 3)
					ss >> parse >> parse >> parse >> delay;
				else if (cnt == 4) {
					ss >> parse >> parse >> data_t;
					type = get_type_from_label(data_t);
				}
				else {
					ss >> parse >> parse >> meta;
					Data D(type, size, age, static_cast<meta_value>(meta));
					(*ref)->add_Data(D);
				}
				cnt = (cnt + 1) % MAX_PARAMS;
			}
			else {
				if (!node_temp) {
					node_temp = new Node(id_counter);
					ref = &node_temp;
				}
				else {
					nodes.push_back(*ref);
					cout << "Added node " << id_counter + 1 << " to simulation.\n";
					node_temp = new Node(++id_counter);
				}
			}
		}
		// add the last node in
		cout << "Added node " << id_counter + 1 << " to simulation.\n";
		nodes.push_back(node_temp);
	}
	else
		cout << "File could not be opened.\n";
}

void Simulator::run(int begin, int end) {
	for(int i = begin; i <= end; i++) {
		stringstream temp;
		temp << "test_" << i << ".txt";
		// first read the random test data generated
		read_data(temp.str());
		cout << "Simulation is starting...\n";
		// run simulation with specified simulation method
		Algorithm* A = Algorithm_Factory::get_algorithm(st);
		A->work(nodes);
	}
}
