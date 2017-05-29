#pragma once

#include "Global.h"
#include "Data.h"

typedef uint64_t		nodeid_t;

class Node {
	
	public:
		
		Node(nodeid_t n) : node_id(n) { }
		
		void add_Data(Data& D) {
			data_arr.push_back(D);
		}
		
		void pop_Data() {
			data_arr.pop_back();
		}
		
		nodeid_t get_id() {
			return node_id;
		}
		
		void set_id(nodeid_t n) {
			node_id = n;
		}
		
		vector<Data>& get_allData() {
			return data_arr;
		}
		
	private:
		
		nodeid_t			node_id;				// Unique id of the node
		vector<Data>		data_arr;				// Vector of Data contained in this node
		
};