/* Mylibc Generic Linked List
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
/* memcpy */
#include <string.h>

#include "mlist.h"

Node * node_init(size_t size_of_type){
    Node * node = malloc(size_of_type);
    node->data = malloc(size_of_type);
    if (node->data == NULL){
        free(node);
        node = NULL;
    }
    return node;
}

void node_destruct(Node ** self){
    free((*self)->data);
    free(*self);
    *self = NULL;
}

List * list_init(size_t size_of_type){
    List * list = (List *) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->size_of_type = size_of_type;
    return list;
}

void list_destruct(List ** self){
	free(*self);
	*self = NULL;
}

Status list_insert_front(List * self, void * read_location){
    Node * node = node_init(self->size_of_type);
    Status status = ERROR_MEM_ALOC;
    if (node){
        node->next = self->head;
        self->head = node;
        if (self->size == 0)
            self->tail = node;

        memcpy(node->data, read_location, self->size_of_type);
        self->size++;
    }

    return status;
}

Status list_insert_back(List * self, void * read_location){
    Node * node = node_init(self->size_of_type);
    Status status = ERROR_MEM_ALOC;
    if (node){
        node->next = NULL;
        if (self->size == 0)
            self->head = node;
        if (self->size > 0)
            self->tail->next = node;
        self->tail = node;

        memcpy(node->data, read_location, self->size_of_type);
        self->size++;
    }

    return status;
}

Status list_insert_at(List * self, void * read_location, u_int64_t index){
    Status status = SUCESS;
    if (index == 0)
        list_insert_front(self, read_location);
    else if (index == self->size)
        list_insert_back(self, read_location);
    else {
        status = INVALID_INDEX;
        if (index < self->size){
            Node * node = node_init(self->size_of_type);
            if (node == NULL)
                status = ERROR_MEM_ALOC;
            else{
                Node * find_previous = self->head;
                uint64_t counter;
                for (counter=0; counter<index-1; counter++)
                    find_previous = find_previous->next;

                node->next = find_previous->next;
                find_previous->next = node;

                memcpy(node->data, read_location, self->size_of_type);
                self->size++;
            }
        }
    }

    return status;
}

void list_clear(List * self){
    while(self->size > 0)
        list_remove_front(self);
}

Status list_get(List * self, void * write_location, u_int64_t index){
     Status status = SUCESS;
    if (self->size == 0){
        status = EMPTY_LIST;
    } else {
        Node * find = self->head;
        uint64_t counter;
        for (counter=0; counter<index; counter++)
            find = find->next;
        memcpy(write_location, find->data, self->size_of_type);
    }
}

Status list_remove_front(List * self){
    Status status = SUCESS;
    if (self->size == 0){
        status = EMPTY_LIST;
    } else if (self->size == 1){
        free(self->head);
        self->head = NULL;
        self->tail = NULL;
        self->size = 0;
    } else {
        Node * remove =  self->head;
        self->head = remove->next;
        free(remove);
        self->size--;
    }
    return status;
}

Status list_remove_back(List * self){
    Status status = SUCESS;
    if (self->size == 0){
        status = EMPTY_LIST;
    } else if (self->size == 1){
        list_remove_front(self);
    } else {
        Node * previous_remove = self->head;
        while(previous_remove->next->next)
            previous_remove = previous_remove->next; 
        Node * remove = previous_remove->next;
        free(remove);
        previous_remove->next = NULL;
    }
    return status;
}

Status list_remove_at(List * self, u_int64_t index){
    Status status = INVALID_INDEX;
    if (self->size == 0)
        status = EMPTY_LIST;
    else if (index == 0)
        list_remove_front(self);
    else if (index == self->size-1)
        list_remove_back(self);
    else if (index < self->size) {
        Node * find_previous = self->head;
        uint64_t counter;
        for (counter=1; counter<index; counter++)
            find_previous = find_previous->next;
        Node * remove = find_previous->next;
        free(remove);
        find_previous->next = find_previous->next->next;
        self->size--;
    }

    return status;
}

Status list_front(List * self, void * write_location){
    Status status = SUCESS;
    if (self->size == 0)
        status = EMPTY_LIST;
    else
        memcpy(write_location, self->head->data, self->size_of_type);
    return status;
}

Status list_back(List * self, void * write_location){
    Status status = SUCESS;
    if (self->size == 0)
        status = EMPTY_LIST;
    else
        memcpy(write_location, self->tail->data, self->size_of_type);
    return status;
}

char * list_str_double_format(List * self){
    char * str = NULL;
    if (self->size == 0){
        printf("[]\n");
    } else {
        /* [val1, val2, ..., valn] */
        size_t str_size = DOUBLE_PRINT_SIZE * self->size + 1 + 2 * self->size;
        str = (char *) malloc(str_size);
        if (str){
            int offset = 0;
            Node * node_print = self->head;
            offset += sprintf(str + offset, "[");
            while (node_print) {
                offset += sprintf(str + offset, "%.16f", *((double *) (node_print->data)));
                if (node_print->next)
                    offset += sprintf(str + offset, ",");
                node_print = node_print->next;
            }
            offset += sprintf(str + offset, "]\n");
        } else 
            fprintf(stderr, "The list could not be printed: memory allocation failed.");
    }
    return str;
}
