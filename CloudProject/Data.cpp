#include "Data.h"

data_type get_type_from_label(const string& s) {
	int pos = 0;
	for (int i = 0; i < DATA_TYPE_EMERGENCY + 1; ++i)
		if (!s.compare(data_type_labels[i])) {
			pos = i;
			break;
		}
	return static_cast<data_type>(pos);
}