#include <iostream>

#include "Global.h"
#include "Simulator.h"

int main(int agrc, char* argv[]) {
	int begin, end, simt;
	cout << "Enter simulation type\n\t0. FIFO\n\t1. LRU\n\t2. LVF\n\t3. SKF\nType: ";
	cin >> simt;
	Simulator S(static_cast<sim_t>(simt));
	cout << "Enter which test case range to run: ";
	cin >> begin >> end;
	S.run(begin, end);
	return 0;
}
