#include <sstream>

#include "Algorithm_Factory.h"
#include "Simulator.h"

const char* data_type_labels[DATA_TYPE_EMERGENCY + 1] = { "Periodic", "On Demand", "Emergency" };
RNG rgen(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

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

		datasize_t id, size, delay, meta;
		data_type type;
		string data_t;
		// create the test objects from the data read
		while (getline(input, temp)) {
			if (temp[0] != '-') {
				/*
				Sample input
				Node: 1 -- this is the data in the BIG NODE (bad naming...)
				Data size: 31238
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
					ss >> parse >> parse >> parse >> delay;
				else if (cnt == 3) {
					ss >> parse >> parse >> data_t;
					type = get_type_from_label(data_t);
				}
				else {
					ss >> parse >> parse >> meta;
					Data D(id, type, size, 0, static_cast<meta_value>(meta), delay);
					data_count++; // increment data count
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

void Simulator::dump_nodes() {
	for (Node* N : nodes) {
		cout << "Node " << N->get_id() << " Data:\n";
		vector<Data>* dlist = &N->get_allData();
		for (Data& D : *dlist)
			cout << "Data: " << D.get_id() << "\nData size: " << D.get_size() << "\nData Age: " << D.get_age() << "\nData Type: " << D.get_type() << "\nData Meta: " << D.get_meta() << '\n';
	}
}

void Simulator::run(int begin, int end) {
	for (int i = begin; i <= end; ++i) {
		stringstream temp;
		temp << "test_" << i << ".txt";
		// first read the random test data generated
		read_data(temp.str());
		// dump_nodes();
		cout << "Simulation is starting...\n";
		// run the specified algorithm iter many times
		// each iteration, pick a different data to use
		Algorithm* A = Algorithm_Factory::get_algorithm(st);
		Simulation_Result R = A->work(nodes, cache_size, iter, data_count);
		report_result(R);
	}
}

void Simulator::report_result(const Simulation_Result& R) {
	fstream outf("sim_result.txt", std::ios::out);
	outf << "---- Simulation Results ----\n";
	outf << "Hit Ratio: " << R.get_hit_ratio() << "\nMiss Ratio: " << R.get_miss_ratio() << "\nTime-to-hit (ms): " << R.get_time_to_hit() << "\nTotal Cache Delay (ms): " << R.get_total_cache_access_delay();
	cout << "Simulation ended.\n";
}