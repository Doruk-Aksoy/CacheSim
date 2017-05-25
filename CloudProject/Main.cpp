#include <iostream>

#include "Global.h"
#include "Simulator.h"

int main(int agrc, char* argv[]) {
begin:
	vector<uint64_t> data_ids;
	int begin, end;
	uint64_t iterations, cache_count, maxd;
	cout << "The simulator will run FIFO, LRU and SKF on given test files.\nEnter max data count: ";
	cin >> maxd;
	cout << "Enter which test case range to run: (begin end) ";
	cin >> begin >> end;
	// iterations simulate the data access count, more the better
	cout << "How many iterations? ";
	cin >> iterations;
	cout << "Cache size? (How many elements to cache) ";
	cin >> cache_count;
	// populate the data sequence to test for
	Simulator::populate(data_ids, maxd, iterations);
	for (int i = 0; i < MAX_ALGORITHMS; ++i) {
		Simulator S(static_cast<sim_t>(i), iterations, cache_count, data_ids);
		for (int j = begin; j <= end; ++j)
			S.run(j);
	}

	char rep;
	cout << "Do you want to repeat? (Y/N)";
	cin >> rep;

	if (rep == 'Y')
		goto begin;

	return 0;
}
