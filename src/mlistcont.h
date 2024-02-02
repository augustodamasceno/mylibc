/* Mylibc Generic Contiguous Cache-Friendly List  
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MLISTCONT_H
#define _MLISTCONT_H

#define CACHE_SIZE_DEFAULT 65536
#define GROWTH_FACTOR 2
#define NEXT_EVEN(x) (((x) + 1) & ~1)

/* srand, rand, malloc, free */
#include <stdlib.h>
/* Integer Types */
#include <stdint.h>


typedef struct { 
	size_t size_of_type;
    size_t capacity;
	uint64_t size;
	void * data;
} ListCont;


typedef enum {
    STATUS_LISTCONT_SUCCESS,
    STATUS_LISTCONT_ERROR_MEM_ALOC,
    STATUS_LISTCONT_INVALID_INDEX,
    STATUS_LISTCONT_EMPTY_LIST
} StatusListCont;


ListCont _list_cont_init(size_t size_of_type,
						 size_t capacity);
ListCont list_cont_init(size_t size_of_type);
ListCont list_cont_init_capacity(size_t size_of_type,
							     size_t capacity);
void list_cont_destruct(ListCont * self);
StatusListCont list_cont_insert(ListCont * self,
								void * read_location);
StatusListCont list_cont_remove(ListCont * self);
void list_cont_clear(ListCont * self);
StatusListCont list_cont_get(ListCont * self,
						     void * write_location,
						     uint64_t index);
StatusListCont list_cont_set(ListCont * self,
						     void * read_location,
						     uint64_t index);
char * _list_cont_str(ListCont * self,
					  const char * format,
					  size_t item_width,
					  char * separator,
					  size_t separator_width);
char * list_cont_str(ListCont * self,
		             const char * format,
					 size_t item_width);

#endif /* _MLISTCONT_H  */
