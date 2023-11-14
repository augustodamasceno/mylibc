/* Mylibc Generic Queue
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
/* memcpy, strchr */
#include <string.h>

#include "mqueue.h"

Queue * queue_init(size_t size_of_type){
    Queue * queue = (Queue *) malloc(sizeof(Queue));
    queue->list = list_init(size_of_type);
    if (queue->list == NULL){
        free(queue);
        queue = NULL;
    }
    return queue;
}

void queue_destruct(Queue ** self){
    list_destruct(&((*self)->list));
    free(*self);
    *self = NULL;
}

u_int64_t queue_size(Queue * self){
    u_int64_t size = self->list->size;
    return size;
}

StatusList queue_insert(Queue * self, void * read_location){
    StatusList status = list_insert_back(self->list, read_location);
    return status;
}

StatusList queue_remove(Queue * self){
    StatusList status = list_remove_front(self->list);
    return status;
}

StatusList queue_front(Queue * self, void * write_location){
    StatusList status = list_front(self->list, write_location);
    return status;
}

StatusList queue_clear(Queue * self){
    StatusList status = list_clear(self->list);
    return status;
}

char * queue_str(Queue * self, const char * format, size_t item_width){
    char separator[] = " <- ";
    size_t separator_width = 4;
    char * str = _list_str(self->list, format, item_width, separator, separator_width);
    return str;
}