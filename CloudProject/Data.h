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
		
		Data(datasize_t di, data_type dt, datasize_t ds, datasize_t da, meta_value dm, datasize_t dd) : d_id(di), d_type(dt), d_size(ds), d_age(da), d_meta(dm), d_delay(dd) { }
		
		data_type get_type() const {
			return d_type;
		}
		
		datasize_t get_size() const {
			return d_size;
		}

		datasize_t get_age() const {
			return d_age;
		}
		
		datasize_t get_meta() const {
			return d_meta;
		}

		datasize_t get_id() const {
			return d_id;
		}

		datasize_t get_delay() const {
			return d_delay;
		}
		
		void set_type(data_type dt) {
			d_type = dt;
		}
		void set_size(data_type ds) {
			d_size = ds;
		}
		
		void set_age(datasize_t da) {
			d_age = da;
		}
		
		void set_meta(meta_value dm) {
			d_meta = dm;
		}

		// calculates the proposed skf value
		double get_skf_value() const {

		}
		
	private:
		
		datasize_t				d_id;			// Id of the data
		data_type				d_type;			// Type of data
		datasize_t				d_size;			// Size of the data on memory
		datasize_t				d_age;			// Age used for LRU and related
		meta_value				d_meta;			// Meta data used for calculations
		datasize_t				d_delay;		// Used for determining the retrieval delay in us
		
};

data_type get_type_from_label(const string&);

struct data_age_compare {
	bool operator() (const Data& D1, const Data& D2) const {
		return D1.get_age() < D2.get_age();
	}
};

struct data_value_compare {
	bool operator() (const Data& D1, const Data& D2) const {
		return D1.get_meta() < D2.get_meta();
	}
};

struct data_skf_compare {
	bool operator() (const Data& D1, const Data& D2) const {
		return D1.get_skf_value() < D2.get_skf_value();
	}
};

#endif
