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
/* memcpy, strchr */
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
    list_clear(*self);
	free(*self);
	*self = NULL;
}

StatusList list_insert_front(List * self, void * read_location){
    Node * node = node_init(self->size_of_type);
    StatusList status = STATUS_LIST_ERROR_MEM_ALOC;
    if (node){
        node->next = self->head;
        self->head = node;
        if (self->size == 0)
            self->tail = node;

        memcpy(node->data, read_location, self->size_of_type);
        self->size++;
        status = STATUS_LIST_SUCCESS;
    }

    return status;
}

StatusList list_insert_back(List * self, void * read_location){
    Node * node = node_init(self->size_of_type);
    StatusList status = STATUS_LIST_ERROR_MEM_ALOC;
    if (node){
        node->next = NULL;
        if (self->size == 0)
            self->head = node;
        if (self->size > 0)
            self->tail->next = node;
        self->tail = node;

        memcpy(node->data, read_location, self->size_of_type);
        self->size++;
        status = STATUS_LIST_SUCCESS;
    }

    return status;
}

StatusList list_insert_at(List * self, void * read_location, uint64_t index){
    StatusList status = STATUS_LIST_SUCCESS;
    if (index == 0)
        list_insert_front(self, read_location);
    else if (index == self->size)
        list_insert_back(self, read_location);
    else {
        if (index < self->size){
            Node * node = node_init(self->size_of_type);
            if (node == NULL)
                status = STATUS_LIST_ERROR_MEM_ALOC;
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
        } else
            status = STATUS_LIST_INVALID_INDEX;
    }

    return status;
}

StatusList list_clear(List * self){
    StatusList status = STATUS_LIST_SUCCESS;
    if (self->size > 0){
        while(self->size > 0)
            list_remove_front(self);
    } else
        status = STATUS_LIST_EMPTY_LIST;

    return status;
}

StatusList list_get(List * self, void * write_location, uint64_t index){
     StatusList status = STATUS_LIST_SUCCESS;
    if (self->size == 0)
        status = STATUS_LIST_EMPTY_LIST;
    else if (index >= self->size)
        status = STATUS_LIST_INVALID_INDEX;
    else {
        Node * find = self->head;
        uint64_t counter;
        for (counter=0; counter<index; counter++)
            find = find->next;
        memcpy(write_location, find->data, self->size_of_type);
    }
    return status;
}

StatusList list_remove_front(List * self){
    StatusList status = STATUS_LIST_SUCCESS;
    if (self->size == 0){
        status = STATUS_LIST_EMPTY_LIST;
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

StatusList list_remove_back(List * self){
    StatusList status = STATUS_LIST_SUCCESS;
    if (self->size == 0){
        status = STATUS_LIST_EMPTY_LIST;
    } else if (self->size == 1){
        status = list_remove_front(self);
    } else {
        Node * previous_remove = self->head;
        while(previous_remove->next->next)
            previous_remove = previous_remove->next; 
        Node * remove = previous_remove->next;
        free(remove);
        previous_remove->next = NULL;
        self->size--;
    }
    return status;
}

StatusList list_remove_at(List * self, uint64_t index){
    StatusList status = STATUS_LIST_INVALID_INDEX;
    if (self->size == 0)
        status = STATUS_LIST_EMPTY_LIST;
    else if (index == 0)
        status = list_remove_front(self);
    else if (index == self->size-1)
        status = list_remove_back(self);
    else if (index < self->size) {
        Node * find_previous = self->head;
        uint64_t counter;
        for (counter=1; counter<index; counter++)
            find_previous = find_previous->next;
        Node * remove = find_previous->next;
        free(remove);
        find_previous->next = find_previous->next->next;
        self->size--;
        status = STATUS_LIST_SUCCESS;
    }

    return status;
}

StatusList list_front(List * self, void * write_location){
    StatusList StatusList = STATUS_LIST_SUCCESS;
    if (self->size == 0)
        StatusList = STATUS_LIST_EMPTY_LIST;
    else
        memcpy(write_location, self->head->data, self->size_of_type);
    return StatusList;
}

StatusList list_back(List * self, void * write_location){
    StatusList StatusList = STATUS_LIST_SUCCESS;
    if (self->size == 0)
        StatusList = STATUS_LIST_EMPTY_LIST;
    else
        memcpy(write_location, self->tail->data, self->size_of_type);
    return StatusList;
}

char * _list_str(List * self, const char * format, size_t item_width, char * separator, size_t separator_width){
    char * str = NULL;
    if (self->size == 0){
        printf("[]\n");
    } else {
        /* [val1, val2, ..., valn] */
        size_t str_size = 1 + separator_width * self->size + item_width * self->size;
        str = (char *) malloc(str_size);
        if (str){
            int offset = 0;
            Node * node_print = self->head;
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
                    offset += sprintf(str + offset, "%s", separator);
                node_print = node_print->next;
            }
            offset += sprintf(str + offset, "]\n");
        } else 
            fprintf(stderr, "The list could not be printed: memory allocation failed.");
    }
    return str;
}

char * list_str(List * self, const char * format, size_t item_width){
    char separator[] = ",";
    size_t separator_width = 1;
    char * str = _list_str(self, format, item_width, separator, separator_width);
    return str;
}
