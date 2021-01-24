#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"

#define BIAS 2
#define SEGMENTS 4
using namespace std;

String::String() {
	length = 0;
	data = NULL;
}

String::String(const String &str) {
	length = str.length;
	data = new char [length +1];
	if (length == 0 || str.data == NULL) {
		delete[] data;
		data =NULL;
	}
	else{
		strcpy (data ,str.data);
	}	
}

String::String(const char *str) {
	if (str == NULL) {
		data = NULL;
		length = 0;
	}
	else{
		data = new char [strlen(str) +1];
		strcpy (data ,str);
		length = strlen(str);
	}
}

String::~String() {
	if (data != NULL) {
		delete[] data;
	}
}

String& String::operator=(const String &rhs) {
	/* frees previous allocated memory */
	if (data !=NULL) {
		delete[] data;
	}
	length = rhs.length;
	if (length == 0)
	{
		data = NULL;
		return *this;
	}
	else{
		data = new char [length +1];
		strcpy (data ,rhs.data);
		return *this;
	}
}

String& String::operator=(const char *str) {
	/* frees previous allocated memory */
	if (data !=NULL) {
		delete[] data;
	}
	if (str == NULL) {
		data = NULL;
		length = 0;
		return *this;
	}
	length = strlen(str) ;
	data = new char[length+1];
	strcpy(data,str);
	return *this;
}


bool String::equals(const String &rhs) const {
	if (length != rhs.length) {
		return false;
	}
	if (strcmp(data , rhs.data)) {
		return false;
	}
	return true;
}

bool String::equals(const char *rhs) const {
	if (rhs==NULL && data==NULL) {
		return true;
	} else if (rhs == NULL) {
		return false;
	}
	if (!strcmp(data , rhs)) {
		return true;
	} else {
		return false;
	}
}




void String::split(const char *delimiters,String **output,size_t *size) const {
	int num_of_delimitesr = strlen(delimiters);
	int delimiter_cnt = 0;
	/* array of data indexes that point to the start of each substring  */
	size_t string_begin [length]= {0};
	int string_begin_index =1;
	/* creating new string and copiying data to it */
	char tmp_data[length+1];
	if(data==NULL)
	{
		*size=0;
		return;
	}
	strcpy (tmp_data , data);
	// printf("We got here1\n");
	/* searching for delimiters in string , changing the delimiter to '\0' and 
	 * update the string begin array ,also handling continous delimiters*/
	for (size_t i=0; i<length; i++) {
		for (int j=0; j<num_of_delimitesr; j++) {
			if (tmp_data[i] == delimiters[j]) {
				if (i+1<length && tmp_data[i+1]=='\0') {
					delimiter_cnt--;
					break;
				}
				if (string_begin[string_begin_index-1] == i 
					&& tmp_data[i+1]!='\0') {
					string_begin[string_begin_index -1]=i+1;
					tmp_data[i] ='\0';
					continue;
				}
				tmp_data[i] ='\0';
				delimiter_cnt++;
				
				/* if the delimiter is the last char in the string,don't update
				 * the string begin array */
				if (i+1 < length && tmp_data[i+1]!='\0') {
					string_begin[string_begin_index] = i+1;
					string_begin_index++;
					break;
				}
			}
		}
	}
	*size = delimiter_cnt +1;
	if (output == NULL) {
		return;
	}
	*output = new String [delimiter_cnt+1];
	/* updating the output array to contain all the substrings */
	for (int i=0; i<delimiter_cnt +1; i++) {
		String new_string = &(tmp_data[string_begin[i]]);
		(*output)[i] = new_string;
	}
}



int String::to_integer() const {
	return atoi(this->data);
}


String String::trim() const {
	int string_start =0;
	int string_end = this->length-1;
	if (data == NULL || this->length == 0) {
		return *this;
	}
	/* skipping the spaces at the beginning and end of the stirng */
	while ((string_start < string_end) && this->data[string_start]==' ') {
		string_start ++;
	}
	while ((this->data[string_end]== ' ')&& (string_start != string_end)) {
		string_end --;
	}
	if (string_start > string_end) {
		char empty_srt[1] ;
		empty_srt[0] ='\0';
		return String(empty_srt);
	}
	char new_str[string_end-string_start+BIAS];
	new_str[string_end-string_start + BIAS -1] ='\0';
	/* copying only the relevant characters to a new string */
	for (int i=0 ;i<string_end-string_start+BIAS -1 ;i++) { 
		new_str[i] = this->data[string_start+i];
	}
	return String(new_str);
}
