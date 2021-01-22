#include "port.h"
#include <cstdlib>

Port::Port(String pattern) : Field(pattern,PORT) {
	range[0] = 0;
	range [1] = 0;
}


bool Port::set_value(String val) {
	String *str_sub = NULL;
	size_t sub_size = 0;
	/* spliting the port range into max and min */
	val.split("-",&str_sub,&sub_size);
	if (sub_size == 0) {
		delete[] str_sub;
		return false;
	}
	if (range[0] <0 || range[1] <0) {
		delete[] str_sub;
		return false;
	}
	/* checking that the range is in the correct order */
	if (range[1] < range[0]) {
		delete[] str_sub;
		return false;
	}
	range[0] = str_sub[0].trim().to_integer();
	range[1] = str_sub[1].trim().to_integer();
	delete[] str_sub;
	return true;
}

bool Port::match_value(String val) const {
	int port = val.trim().to_integer();
	if ( port >= range[0] && port <= range[1]) {
		return true;
	}
	return false;
}