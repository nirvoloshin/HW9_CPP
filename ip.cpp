#include "ip.h"
#include <cstring>
#include <iostream>

enum {packet_max_size = 255 ,packet_min_size =0 ,one_byte = 8 , two_byte = 16,
		three_byte = 24 ,four_byte = 32 };

enum {firs_octat = 3 , second_octat = 2 , third_octat = 1 , fourth_octat = 0};

Ip::Ip(String pattern) : Field(pattern,IP) {
	this->low = 0;
	this->high = 0;
}

/**
 * @brief change a sting that contains IP to IP num
 * @return the IP num and set error to 0 on success
 * @if the ip num isn't in IP range ser error to 1
 */
unsigned int ip_to_num (String Ip, int *error){
	//adding test that this is IP
	String *str_arr = NULL;
	size_t size = 0;
	Ip.split(".",&str_arr,&size);
	/* checking if each IP byte is in the correct range */
	for (size_t i=0; i<size ;i++) {
		if (str_arr[i].to_integer() >packet_max_size ||
			str_arr[i].to_integer() <packet_min_size) {
			delete[] str_arr;
			*error = 1;
			return 0;
		}
	}
	unsigned int res = 0;
	/* building the full ip num with the ip bytes */
	res = str_arr[fourth_octat].to_integer() << three_byte
		  | str_arr[third_octat].to_integer() << two_byte
		  | str_arr[second_octat].to_integer() << one_byte 
		  | str_arr[firs_octat].to_integer() ;
	delete[] str_arr;
	*error = 0;
	return res;

}

bool Ip::set_value(String val){
	String *str_sub = NULL;
	size_t sub_size = 0;
	/* spliting the ip rule to ip and cidr */
	val.split("/",&str_sub,&sub_size);
	int cidr = str_sub[1].trim().to_integer();
	/* checking that the cidr is in correct range - max four bytes */
	if(cidr > four_byte || cidr < 0){
		delete[] str_sub;
		return false;
	}
	unsigned int mask = 0;
	for(int i=0; i<cidr; i++){
		mask = mask + (1 << (four_byte-1-i)); 
	}
	int error;
	unsigned int ip_num = ip_to_num (str_sub[0].trim() , &error);
	if (error) {
		delete[] str_sub;
		return false;
	}
	this->low =  ip_num & mask;
	this->high = ip_num | (~mask);
	delete[] str_sub;
	return true;
}

bool Ip::match_value(String val) const{
	int error;
	unsigned int ip = ip_to_num(val ,&error);
	if(error) {
		return false;
	}
	if((ip <= this->high) && (ip >= this->low)){
		return true;
	}
	return false;
}


