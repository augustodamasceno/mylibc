/* Mylibc Generic Static Queue
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
/* memcpy, strchr */
#include <string.h>

#include "msqueue.h"
#include "mprint.h"


StaticQueue * squeue_init(size_t size_of_type, uint64_t max_size){
    StaticQueue * squeue = NULL;
	if(max_size > 0){ 
		squeue = (StaticQueue *) malloc(sizeof(StaticQueue));
		squeue->max_size = max_size;
		squeue->size_of_type = size_of_type;
		squeue->values = malloc(size_of_type * max_size);
		squeue_clear(squeue);
		if (squeue->values == NULL){
			free(squeue);
			squeue = NULL;
		}
	}
    return squeue;
}

void squeue_destruct(StaticQueue ** self){
	if (*self != NULL){
		free((*self)->values);
	    free(*self);
		*self = NULL;
	}
}

void squeue_insert(StaticQueue * self, void * read_location){
	char * memory_location = (char *) self->values;
	if (self != NULL && read_location != NULL){
		if (self->size == 0){
			self->front = 0;
			self->back = 0;
		} else if (self->size == self->max_size){
			self->front = (self->front + 1) % self->max_size;
			self->back = (self->back + 1) % self->max_size;
			self->size--;
		} else {
			self->back = (self->back + 1) % self->max_size;
		}
		self->size++;
		memory_location += self->size_of_type * self->back;
		memcpy(memory_location, read_location, self->size_of_type);
	}
}

void squeue_remove(StaticQueue * self){
	if (self != NULL && self->size > 0){
		if (self->size == 1){
			squeue_clear(self);
		} else if (self->front == 0)
			self->front = self->max_size - 1;
		else
			self->front--;
	
		self->size--;
	}
}

void squeue_front(StaticQueue * self, void * write_location){
	char * memory_location = (char *) self->values;
	if (self != NULL && self->size > 0){
		memory_location += self->size_of_type * self->front;
		memcpy(write_location, memory_location, self->size_of_type);
	} else
		write_location = NULL;
}

void squeue_clear(StaticQueue * self){
	self->front = -1;
	self->back = -1;
	self->size = 0;
}

double squeue_sum_double(StaticQueue * self){
	uint64_t print_counter = self->size;
	uint64_t index = self->front;
	double sum = 0;	
	char * memory_location = NULL;
	while (print_counter > 0) {
		memory_location = ((char *) self->values) + index * self->size_of_type;
		index = (index + 1) % self->max_size;
		print_counter--;
		sum += *((double*)(memory_location));
	}
	return sum;
}

char * _squeue_str(StaticQueue * self, 
			const char * format,
			size_t item_width,
			char * separator,
			size_t separator_width){
	char * str = NULL;
	int offset = 0;
	uint64_t index = 0;
	uint64_t print_counter = self->size;
	char * memory_location = (char*)self->values;
	if (self->size == 0){
		str = (char *) malloc(3);
		sprintf(str, "[]");
	} else {
		/* [val1, val2, ..., valn] */
		size_t str_size = 3 + separator_width * self->size + item_width * self->size;
		str = (char *) malloc(str_size);
		if (str){
			offset += sprintf(str + offset, "[");
			index = self->front;
			while (print_counter > 0) {
				memory_location = ((char *) self->values) + index * self->size_of_type;
				index = (index + 1) % self->max_size;
				print_counter--;
				if (format_specifiers_int(format)){
					if (format_specifiers_unsigned(format))
						offset += sprintf(str + offset, format, *((unsigned int*)(memory_location)));
					else
						offset += sprintf(str + offset, format, *((int*)(memory_location)));
				} 
				else if (format_specifiers_long(format)){
					if (format_specifiers_unsigned(format))
						offset += sprintf(str + offset, format, *((unsigned long int*)(memory_location)));
					else
						offset += sprintf(str + offset, format, *((long int*)(memory_location)));
				} 
				else if (format_specifiers_double(format))
					offset += sprintf(str + offset, format, *((double*)(memory_location)));
				else if ((strchr(format, 's') != NULL)
						|| (strchr(format, 'c') != NULL))
					offset += sprintf(str + offset, format, *((char*)(memory_location)));
				else if (strchr(format, 'p') != NULL)
					offset += sprintf(str + offset, format, memory_location);
				else
					offset += sprintf(str + offset, "?");

				if (print_counter >= 1)
					offset += sprintf(str + offset, "%s", separator);	
			}
			offset += sprintf(str + offset, "]");
		} else 
			fprintf(stderr, "The list could not be printed: memory allocation failed.");
	}
	return str;
}

char * squeue_str(StaticQueue * self, const char * format, size_t item_width){
    char separator[] = " <- ";
    size_t separator_width = 4;
    char * str = _squeue_str(self, format, item_width, separator, separator_width);
    return str;
}

