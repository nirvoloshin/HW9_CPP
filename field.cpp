/* Includes */
#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>


Field::Field(String pattern, field_type type ) : pattern(pattern), type(type){
}

Field::Field(String pattern) {
	this->pattern = pattern ;
	this ->type = GENERIC;
}

Field::~Field() {}

field_type Field::get_type() const {
	return this->type;
}

bool Field::set_value(String val) {
	if (this->type == IP){
		return ((Ip*)this)->set_value(val);
	}
	if( this->type == PORT){
		return ((Port*)this)->set_value(val);
	}
	return false;
}

bool Field::match_value(String val) const {
	if (this->type == IP){
		return ((Ip*)this)->match_value(val);
	}
	if( this->type == PORT){
		return ((Port*)this)->match_value(val);
	}
	return false;
}

bool Field::match(String packet) {
	size_t field_cnt=0;
	String *str_arr=NULL;
	/* Now we place the packet's sub fields in the array */
	packet.split(",=",&str_arr,&field_cnt);
	if(field_cnt == 0){
		delete[] str_arr;
		return false;
	}
	/* checking each sub field if it matches the rule */
	for(size_t i=0; i<field_cnt; i++){
		if(str_arr[i].trim().equals(this->pattern.trim())){
			bool res = this->match_value(str_arr[i+1].trim());
			delete[] str_arr;
			return res;
		}
	}
	delete[] str_arr;
	return false;
}

