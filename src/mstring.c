/* Mylibc String
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include "mstring.h"

uint8_t char_in(const char * string, const char c){
	uint8_t is_in = 0;
	uint64_t index = 0;
	if (string != NULL){
		while(string[index] != '\0'){
			if (string[index] == c){
				is_in = 1;
				break;
			}
			index++;
		}
	}
	return is_in;
}

uint8_t string_contains(const char * string, const char * chars){
	uint8_t contain = 0;
	uint64_t index_string = 0;
	uint64_t index_chars = 0;
	if (string != NULL && chars != NULL){
		while(string[index_string] != '\0'){
			index_chars = 0;
			while (chars[index_chars] != '\0'){
				if (string[index_string] == chars[index_chars]){
					contain = 1;
					break;
				}
				index_chars++;
			}
			if (contain)
				break;
			index_string++;
		}
	}
	return contain;
}

char * string_remove(const char * string, const char * chars){
	uint64_t index_string = 0;
	uint64_t index_striped = 0;
	uint64_t size_string = string_size(string);
	char * striped = NULL;
	if (string != NULL && chars != NULL){
		striped = (char*) malloc(sizeof(char) * (size_string+1));
		while(string[index_string] != '\0'){
			if (char_in(chars, string[index_string]) == 0){
				striped[index_striped] = string[index_string];
				index_striped++;	
			}
			index_string++;
		}
		striped[index_striped] = '\0';
	}
	return striped;
}

uint64_t string_size(const char * string){
	uint64_t counter = 0;
	if (string != NULL){
		while(string[counter] != '\0')
			counter++;
	}
	return counter;
}

uint64_t string_count_char(const char * string,
						   char c){
	uint64_t occurrences = 0;
	uint64_t index = 0;
	if (string != NULL){
		while(string[index] != '\0'){
			if (string[index] == c)
				occurrences++;
			index++;
		}
	}
	return occurrences;
}

char * string_cut(const char * string,
				  uint64_t start,
				  uint64_t end){
	uint64_t size_string = 0;	
	uint64_t index_string = 0;
	uint64_t index_cut = 0;
	uint64_t fixed_end = end;
	char * cut = NULL;
	if (string != NULL)
		size_string = string_size(string);

	if (   size_string > 0
		&& start < size_string
		&& start <= end){
		if (end >= size_string)
			fixed_end = size_string-1;
		cut = (char*) malloc(fixed_end-start+2);
		for (index_string=start; index_string<=fixed_end; index_string++){
			cut[index_cut] = string[index_string];
			index_cut++;
		}
		cut[index_cut] = '\0';
	}
	return cut;
};

uint64_t string_count(const char * string,
					  const char * substring){
	char * cut = NULL;
	uint64_t occurrences = 0;
	uint64_t index = 0;
	uint64_t jump = 0;
	uint64_t size_string = string_size(string);
	uint64_t size_substring = string_size(substring);
	if (size_string >= size_substring){
		index=0;
		while(index<=size_string-size_substring){
			jump = 1;
			cut = string_cut(string, index, index+size_substring-1);
			if (cut != NULL){
				if (strcmp(cut, substring) == 0){
					occurrences++;
					jump = size_substring; 
				}
				free(cut);
			}
			index += jump;
		}
	}
	return occurrences;
}

char ** string_split(const char * string,
				  const char * separator,
				  uint64_t * size){
	uint64_t size_string = string_size(string);
	uint64_t size_separator = string_size(separator);	
	uint64_t num_substring = 0;
	uint64_t index = 0;
	uint64_t index_substring = 0;
	uint64_t jump = 0;
	char * cut = NULL;
	char ** strings = NULL;
	*size = 0;
	strings = NULL;
	if (size_string >= size_separator){
		*size = 1 + string_count(string, separator);
		strings = (char**) malloc(sizeof(char*)*(*size));
		for (index=0; index<*size; index++){
			strings[index] = (char*) malloc(sizeof(char)*(size_string+1));
			strings[index][0] = '\0';
		}
		index_substring = 0;
		index = 0;
		while(index<=size_string){
			jump = 1;
			cut = string_cut(string, index, index+size_separator-1);
			if (cut != NULL){
				if (strcmp(cut, separator) == 0){
					jump = size_separator; 
					strings[num_substring][index_substring+1] = '\0';
					num_substring++;
					index_substring = -1;
				} else
					strings[num_substring][index_substring] = string[index];

				free(cut);
			}
			index += jump;
			index_substring++;
		}
	}
	return strings;
}

