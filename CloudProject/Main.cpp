#include <iostream>

#include "Global.h"
#include "Simulator.h"

int main(int agrc, char* argv[]) {
	int begin, end, simt;
	uint64_t iterations, cache_count;
	cout << "Enter simulation type\n\t0. FIFO\n\t1. LRU\n\t2. LVF\n\t3. SKF\nType: ";
	cin >> simt;
	cout << "Enter which test case range to run: (begin end) ";
	cin >> begin >> end;
	// iterations simulate the data access count, more the better
	cout << "How many iterations? ";
	cin >> iterations;
	cout << "Cache size? (How many elements to cache) ";
	cin >> cache_count;
	Simulator S(static_cast<sim_t>(simt), iterations, cache_count);
	S.run(begin, end);

	int x;
	cin >> x;

	return 0;
}
