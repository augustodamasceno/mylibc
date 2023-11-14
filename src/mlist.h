/* Mylibc Generic Linked List
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MLIST_H
#define _MLIST_H

/* srand, rand, malloc, free */
#include <stdlib.h>
/* Integer Types */
#include <stdint.h>

#define TRUE 1
#define FALSE 0


struct Node;
typedef struct {
    struct Node * head;
    struct Node * tail;
    u_int64_t size;
    size_t size_of_type;
} List;

typedef struct Node {
    void * data;
    struct Node * next;
} Node;

typedef enum {
    STATUS_LIST_SUCCESS,
    STATUS_LIST_ERROR_MEM_ALOC,
    STATUS_LIST_INVALID_INDEX,
    STATUS_LIST_EMPTY_LIST
} StatusList;


Node * node_init(size_t size_of_type);
void node_destruct(Node ** self);
List * list_init(size_t size_of_type);
void list_destruct(List ** self);
StatusList list_insert_front(List * self, void * read_location);
StatusList list_insert_back(List * self, void * read_location);
StatusList list_insert_at(List * self, void * read_location, u_int64_t index);
StatusList list_remove_front(List * self);
StatusList list_remove_back(List * self);
StatusList list_remove_at(List * self, u_int64_t index);
StatusList list_clear(List * self);
StatusList list_get(List * self, void * write_location, u_int64_t index);
StatusList list_front(List * self, void * write_location);
StatusList list_back(List * self, void * write_location);
char * _list_str(List * self, const char * format, size_t item_width, char * separator, size_t separator_width);
char * list_str(List * self, const char * format, size_t item_width);


#endif /* _MLIST_H  */
