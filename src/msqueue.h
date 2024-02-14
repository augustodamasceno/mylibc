/* Mylibc Generic Static Queue
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MSQUEUE_H
#define _MSQUEUE_H

#include <stdlib.h>
#include <stdint.h>


typedef struct {
    void * values;
	size_t size_of_type;
	int front;
	int back;
	uint64_t size;
	uint64_t max_size;
} StaticQueue;

StaticQueue * squeue_init(size_t size_of_type, uint64_t max_size);
void squeue_destruct(StaticQueue ** self);
void squeue_insert(StaticQueue * self, void * read_location);
void squeue_remove(StaticQueue * self);
void squeue_front(StaticQueue * self, void * write_location);
void squeue_clear(StaticQueue * self);
double _squeue_sum_double(StaticQueue * self, uint8_t ignore_nan);
double squeue_sum_double(StaticQueue * self);
double squeue_sumnan_double(StaticQueue * self);
char * _squeue_str(StaticQueue * self, 
				   const char * format,
				   size_t item_width,
				   char * separator,
				   size_t separator_width);
char * squeue_str(StaticQueue * self, const char * format, size_t item_width);

#endif /* _MSQUEUE_H  */
