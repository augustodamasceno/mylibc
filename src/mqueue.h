/* Mylibc Generic Queue
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MQUEUE_H
#define _MQUEUE_H

/* srand, rand, malloc, free */
#include <stdlib.h>
/* Integer Types */
#include <stdint.h>

#include "mlist.h"


typedef struct {
    List * list;
} Queue;

Queue * queue_init(size_t size_of_type);
void queue_destruct(Queue ** self);
uint64_t queue_size(Queue * self);
StatusList queue_insert(Queue * self, void * read_location);
StatusList queue_remove(Queue * self);
StatusList queue_front(Queue * self, void * write_location);
StatusList queue_clear(Queue * self);
char * queue_str(Queue * self, const char * format, size_t item_width);

#endif /* _MQUEUE_H  */
