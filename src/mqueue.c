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
}

char * queue_str(Queue * self, const char * format, size_t item_width){
  char * str = NULL;
    if (self->list->size == 0){
        printf("[]\n");
    } else {
        /* [val1, val2, ..., valn] */
        size_t str_size = 1 + 4 * self->list->size + item_width * self->list->size;
        str = (char *) malloc(str_size);
        if (str){
            int offset = 0;
            Node * node_print = self->list->head;
            offset += sprintf(str + offset, "[");
            while (node_print) {
                if ((strchr(format, 'd') != NULL) 
                    || (strchr(format, 'i') != NULL) 
                    || (strchr(format, 'l') != NULL)
                    || (strchr(format, 'h') != NULL)
                    || (strchr(format, 'j') != NULL)
                    || (strchr(format, 'z') != NULL)
                    || (strchr(format, 't') != NULL))
                    offset += sprintf(str + offset, format, *((long int*)(node_print->data)));
                else if ((strchr(format, 'u') != NULL) 
                        || (strchr(format, 'o') != NULL) 
                        || (strchr(format, 'x') != NULL)
                        || (strchr(format, 'X') != NULL)) 
                    offset += sprintf(str + offset, format, *((unsigned long int*)(node_print->data)));
                else if ((strchr(format, 'f') != NULL) 
                            || (strchr(format, 'F') != NULL) 
                            || (strchr(format, 'e') != NULL)
                            || (strchr(format, 'E') != NULL)
                            || (strchr(format, 'g') != NULL)
                            || (strchr(format, 'G') != NULL)
                            || (strchr(format, 'a') != NULL)
                            || (strchr(format, 'A') != NULL))
                    offset += sprintf(str + offset, format, *((double*)(node_print->data)));
                else if ((strchr(format, 's') != NULL)
                        || (strchr(format, 'c') != NULL))
                    offset += sprintf(str + offset, format, *((char*)(node_print->data)));
                else if (strchr(format, 'p') != NULL)
                    offset += sprintf(str + offset, format, node_print->data);
                else
                    offset += sprintf(str + offset, "?");

                if (node_print->next)
                    offset += sprintf(str + offset, " <- ");
                node_print = node_print->next;
            }
            offset += sprintf(str + offset, "]\n");
        } else 
            fprintf(stderr, "The list could not be printed: memory allocation failed.");
    }
    return str;
}