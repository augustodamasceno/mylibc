/* Mylibc Generic Contiguous Cache-Friendly List  
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include "mlistcont.h"
#include "mprint.h"


ListCont _list_cont_init(size_t size_of_type,
						 size_t capacity){
	ListCont list;
	list.size_of_type = size_of_type;	
	list.capacity = capacity;
	list.size = 0;
	list.data = malloc(capacity * size_of_type);
	if (list.data == NULL)
		list_cont_destruct(&list);
	return list;
}

ListCont list_cont_init(size_t size_of_type){
	ListCont list = _list_cont_init(size_of_type, CACHE_SIZE_DEFAULT);
	return list;
}

ListCont list_cont_init_capacity(size_t size_of_type,
								 size_t capacity){
	ListCont list = _list_cont_init(size_of_type, NEXT_EVEN(capacity));
	return list;
}

void list_cont_destruct(ListCont * self){
	if (self->data != NULL){
		free(self->data);
		self->data = NULL;
	}
	self->capacity = 0;
	self->size = 0;
	self->size_of_type = 0;
}

StatusListCont list_cont_insert(ListCont * self,
								void * read_location){
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	size_t new_capacity = 0;
	void * new_data = NULL;
	if (self->size == self->capacity){
		new_capacity = NEXT_EVEN(self->capacity * GROWTH_FACTOR);
		new_data = malloc(new_capacity * self->size_of_type);
		if (new_data == NULL)
			status = STATUS_LISTCONT_ERROR_MEM_ALOC;
		else {
			memcpy(new_data, self->data, self->capacity * self->size_of_type);
			free(self->data);
			self->data = new_data;
			self->capacity = new_capacity;
		}
	}
	if (status == STATUS_LISTCONT_SUCCESS){
		self->size++;
		list_cont_set(self, read_location, self->size-1);
	}

	return status;
}

StatusListCont list_cont_remove(ListCont * self){
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	if (self->size == 0)
		status = STATUS_LISTCONT_EMPTY_LIST;
	else
		self->size--;
	return status;
}

void list_cont_clear(ListCont * self){
	self->size = 0;
}

StatusListCont list_cont_get(ListCont * self,
							 void * write_location,
							 uint64_t index){
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	char * memory_location = (char*) self->data;
	if (index < self->size){
		memory_location += self->size_of_type * index;
		memcpy(write_location, memory_location, self->size_of_type);
	} else
		status = STATUS_LISTCONT_INVALID_INDEX;
	return status;
}

StatusListCont list_cont_set(ListCont * self,
							 void * read_location,
							 uint64_t index){
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	char * memory_location = (char*) self->data;
	if (index < self->size){
		memory_location += self->size_of_type * index;
		memcpy(memory_location, read_location, self->size_of_type);
	} else
		status = STATUS_LISTCONT_INVALID_INDEX;
	return status;
}

char * _list_cont_str(ListCont * self,
					  const char * format,
					  size_t item_width,
					  char * separator,
					  size_t separator_width){
	char * str = NULL;
	int offset = 0;
	uint64_t index = 0;
	char * memory_location = (char*)self->data;
	if (self->size == 0){
		str = (char *) malloc(3);
		sprintf(str, "[]");
	} else {
		/* [val1, val2, ..., valn] */
		size_t str_size = 3 + separator_width * self->size + item_width * self->size;
		str = (char *) malloc(str_size);
		if (str){
			offset += sprintf(str + offset, "[");
			for (index=0; index<self->size; index++) {
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

				if (index < self->size-1)
					offset += sprintf(str + offset, "%s", separator);
				
				memory_location += self->size_of_type;
			}
			offset += sprintf(str + offset, "]");
		} else 
			fprintf(stderr, "The list could not be printed: memory allocation failed.");
	}
	return str;
}

char * list_cont_str(ListCont * self,
					 const char * format,
					 size_t item_width){
	char separator[] = ",";
	size_t separator_width = 1;
	char * str = _list_cont_str(self, format, item_width, separator, separator_width);
	return str;
}

