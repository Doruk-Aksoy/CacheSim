#ifndef DATA_IN
#define DATA_IN

#include "Global.h"

enum data_type {
	DATA_TYPE_PERIODIC,
	DATA_TYPE_ONDEMAND,
	DATA_TYPE_EMERGENCY
};

extern const char* data_type_labels[DATA_TYPE_EMERGENCY + 1];

enum meta_value {
	META_BIN,
	META_TXT,
	META_IMAGE,
	META_SOUND,
	META_VIDEO
};

typedef uint64_t				datasize_t;

class Data {
	
	public:
		
		Data(data_type dt, datasize_t ds, datasize_t da, meta_value dm) : d_type(dt), d_size(ds), d_age(da), d_meta(dm) { }
		
		data_type get_type() {
			return d_type;
		}
		
		datasize_t get_size() {
			return d_size;
		}

		datasize_t get_age() {
			return d_age;
		}
		
		datasize_t get_meta() {
			return d_meta;
		}
		
		void set_type(data_type dt) {
			d_type = dt;
		}
		void set_size(data_type ds) {
			d_size = ds;
		}
		
		void set_age(data_type da) {
			d_age = da;
		}
		
		void set_meta(meta_value dm) {
			d_meta = dm;
		}
		
	private:
		
		data_type				d_type;			// Type of data
		datasize_t				d_size;			// Size of the data on memory
		datasize_t				d_age;			// Age used for LRU and related
		meta_value				d_meta;			// Meta data used for calculations
		datasize_t				d_pos;			// Used for determining the retrieval delay
		
};

data_type get_type_from_label(const string&);

#endif
