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
#define DOUBLE_PRINT_SIZE 81


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
    SUCESS,
    ERROR_MEM_ALOC,
    INVALID_INDEX,
    EMPTY_LIST
} Status;

Node * node_init(size_t size_of_type);
void node_destruct(Node ** self);
List * list_init(size_t size_of_type);
void list_destruct(List ** self);
Status list_insert_front(List * self, void * read_location);
Status list_insert_back(List * self, void * read_location);
Status list_insert_at(List * self, void * read_location, u_int64_t index);
Status list_remove_front(List * self);
Status list_remove_back(List * self);
Status list_remove_at(List * self, u_int64_t index);
void list_clear(List * self);
Status list_get(List * self, void * write_location, u_int64_t index);
Status list_front(List * self, void * write_location);
Status list_back(List * self, void * write_location);
char * list_str_double_format(List * self);

#endif /* _MLIST_H  */
