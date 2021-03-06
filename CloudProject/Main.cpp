#include <iostream>

#include "Global.h"
#include "Simulator.h"

int main(int agrc, char* argv[]) {
begin:
	int begin, end, dist;
	uint64_t iterations, cache_count, maxd, numseq;
	cout << "The simulator will run FIFO, LRU, SKF and Optimal (Look Ahead) on given test files.\nEnter max data count: ";
	cin >> maxd;
	cout << "Enter which test case range to run (begin end): ";
	cin >> begin >> end;
	cout << "Enter the amount of distinct number sequences to be generated: ";
	cin >> numseq;
	cout << "Uniform or exponential distribution? (0 - 1): ";
	cin >> dist;
	// iterations simulate the data access count, more the better
	cout << "How many iterations? ";
	cin >> iterations;
	cout << "Cache size? (How many elements to cache) ";
	cin >> cache_count;

	// Reset accumulations
	Simulation_Result::reset();
	// populate the data sequence to test for
	vector<vector<uint64_t>> wholeseq(numseq);
	for (int i = 0; i < numseq; ++i)
		Simulator::populate(wholeseq[i], maxd, iterations, dist);
	for (int i = 0; i < MAX_ALGORITHMS; ++i) {
		Simulator S(static_cast<sim_t>(i), iterations, cache_count);
		for (int j = begin; j <= end; ++j)
			S.run(j, wholeseq);
	}
	Simulator::report_summary(end - begin + 1, numseq);

	char rep;
	cout << "Do you want to repeat? (Y/N)";
	cin >> rep;

	if (rep == 'Y')
		goto begin;

	return 0;
}
