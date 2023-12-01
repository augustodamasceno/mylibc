/* Mylibc List Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>

#include "test_mlist.h"
#include "../src/mlist.h"


START_TEST (testListInitDestruct) {
	List * list = list_init(sizeof(double));
	ck_assert_ptr_nonnull(list);

	ck_assert_int_eq(0, list->size);
	ck_assert_int_eq(sizeof(double), list->size_of_type);
	ck_assert_ptr_null(list->head);
	ck_assert_ptr_null(list->tail);

	list_destruct(&list);
	ck_assert_ptr_null(list);
}

START_TEST (testListInsertFront) {
	char * str = NULL;
	double read = -1;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(double));
	ck_assert_ptr_nonnull(list);

	read = 100;
	status = list_insert_front(list, (void *)&read);
	ck_assert_int_eq(1, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.1f", 5);
	ck_assert_str_eq(str, "[100.0]");
	free(str);

	read = 0.123;
	status = list_insert_front(list, (void *)&read);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[0.123,100.000]");
	free(str);

	read = -456;
	status = list_insert_front(list, (void *)&read);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 8);
	ck_assert_str_eq(str, "[-456.000,0.123,100.000]");
	free(str);

	list_destruct(&list);
}

START_TEST (testListInsertBack) {
	char * str = NULL;
	double read = -1;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(double));
	ck_assert_ptr_nonnull(list);

	read = 100;
	status = list_insert_back(list, (void *)&read);
	ck_assert_int_eq(1, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.1f", 5);
	ck_assert_str_eq(str, "[100.0]");
	free(str);

	read = 0.123;
	status = list_insert_back(list, (void *)&read);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[100.000,0.123]");
	free(str);

	read = -456;
	status = list_insert_back(list, (void *)&read);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 8);
	ck_assert_str_eq(str, "[100.000,0.123,-456.000]");
	free(str);

	list_destruct(&list);
}

START_TEST (testListInsertAt) {
	char * str = NULL;
	int read = -1;
	uint64_t index = 0;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	ck_assert_ptr_nonnull(list);

	/* Try to insert in an invalid index. */
	read = 9;
	index = 10;
	status = list_insert_at(list, (void *)&read, index);
	ck_assert_int_eq(0, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_INVALID_INDEX);

	/* Empty list. */
	read = 1;
	index = 0;
	status = list_insert_at(list, (void *)&read, index);
	ck_assert_int_eq(1, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[1]");
	free(str);

	/* Index equal to the size of the list. */
	read = 2;
	index = 1;
	status = list_insert_at(list, (void *)&read, index);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[1,2]");
	free(str);

	/* Index in the middle of the list. */
	read = 3;
	status = list_insert_at(list, (void *)&read, 1);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[1,3,2]");
	free(str);

	list_destruct(&list);
}

START_TEST (testListRemoveFront) {
	int read = 1;
	char * str = NULL;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	list_insert_back(list, (void *)&read);
	read = 2;
	list_insert_back(list, (void *)&read);
	read = 3;
	list_insert_back(list, (void *)&read);

	/* Remove front list more than 2 items */
	status = list_remove_front(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(2, list->size);
	str = list_str(list, "%d", 5);
	ck_assert_str_eq(str, "[2,3]");
	free(str);

	/* Remove front list with 1 item */
	status = list_remove_front(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(1, list->size);
	str = list_str(list, "%d", 5);
	ck_assert_str_eq(str, "[3]");
	free(str);
	
	/* Remove front list with 1 item */
	status = list_remove_front(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(0, list->size);

	/* Remove front empty list */
	status = list_remove_front(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_EMPTY_LIST);
	ck_assert_int_eq(0, list->size);

	list_destruct(&list);
}

START_TEST (testListRemoveBack) {
	int read = 1;
	char * str = NULL;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	list_insert_back(list, (void *)&read);
	read = 2;
	list_insert_back(list, (void *)&read);
	read = 3;
	list_insert_back(list, (void *)&read);

	/* Remove front list more than 2 items */
	status = list_remove_back(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(2, list->size);
	str = list_str(list, "%d", 5);
	ck_assert_str_eq(str, "[1,2]");
	free(str);

	/* Remove front list with 1 item */
	status = list_remove_back(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(1, list->size);
	str = list_str(list, "%d", 5);
	ck_assert_str_eq(str, "[1]");
	free(str);
	
	/* Remove front list with 1 item */
	status = list_remove_back(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(0, list->size);

	/* Remove front empty list */
	status = list_remove_back(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_EMPTY_LIST);
	ck_assert_int_eq(0, list->size);

	list_destruct(&list);
}

START_TEST (testListRemoveAt) {
	int read = 0;
	char * str = NULL;
	uint64_t index = 0;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	for (read=1; read<10; read++)
		list_insert_back(list, (void *)&read);

	/* Remove at front */
	index = 0;
	status = list_remove_at(list, index);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[2,3,4,5,6,7,8,9]");
	ck_assert_int_eq(8, list->size);
	free(str);

	/* Remove at back */
	index = 7;
	status = list_remove_at(list, index);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[2,3,4,5,6,7,8]");
	ck_assert_int_eq(7, list->size);
	free(str);

	/* Remove at middle */
	index = 3;
	status = list_remove_at(list, index);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	printf("%s", str);
	ck_assert_str_eq(str, "[2,3,4,6,7,8]");
	ck_assert_int_eq(6, list->size);
	free(str);

	/* Remove at invalid index */
	index = 100;
	status = list_remove_at(list, index);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_INVALID_INDEX);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[2,3,4,6,7,8]");
	ck_assert_int_eq(6, list->size);
	free(str);

	list_destruct(&list);
}

START_TEST (testListClear) {
	int read = 2;
	uint8_t index = 0;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	for (index=0; index<5; index++)
		list_insert_back(list, (void *)&read);

	status = list_clear(list);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(0, list->size);

	list_destruct(&list);
}

START_TEST (testListGet) {
	int read = 0;
	int write = 0;
	uint64_t index = 0;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	for (read=1; read<10; read++)
		list_insert_back(list, (void *)&read);

	/* Get at front */
	index = 0;
	status = list_get(list, (void *)&write, index);
	ck_assert_int_eq(1, write);

	/* Get at back */
	index = 8;
	status = list_get(list, (void *)&write, index);
	ck_assert_int_eq(9, write);

	/* Get at middle */
	index = 6;
	status = list_get(list, (void *)&write, index);
	ck_assert_int_eq(7, write);

	/* Get at invalid index */
	index = 100;
	write = 123;
	status = list_get(list, (void *)&write, index);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_INVALID_INDEX);
	ck_assert_int_eq(123, write);

	list_destruct(&list);
}

START_TEST (testListFront) {
	int read = 3;
	int write = 8;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	read = 1;
	list_insert_front(list, (void *)&read);
	read = 7;
	list_insert_front(list, (void *)&read);
	read = 100;
	list_insert_front(list, (void *)&read);

	status = list_front(list, (void *)&write);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(read, write);

	list_destruct(&list);
}

START_TEST (testListBack) {
	int read = 3;
	int write = 8;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;

	List * list = list_init(sizeof(int));
	read = 1;
	list_insert_back(list, (void *)&read);
	read = 7;
	list_insert_back(list, (void *)&read);
	read = 100;
	list_insert_back(list, (void *)&read);

	status = list_back(list, (void *)&write);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	ck_assert_int_eq(read, write);

	list_destruct(&list);
}

Suite* suite_mlist(){
    Suite* suite = suite_create("List Suite");
    TCase* tc_list= tcase_create("List");

    tcase_add_test(tc_list, testListInitDestruct);
	tcase_add_test(tc_list, testListInsertFront);
    tcase_add_test(tc_list, testListInsertBack);
	tcase_add_test(tc_list, testListInsertAt);
	tcase_add_test(tc_list, testListRemoveFront);
	tcase_add_test(tc_list, testListRemoveBack);
	tcase_add_test(tc_list, testListRemoveAt);
	tcase_add_test(tc_list, testListClear);
	tcase_add_test(tc_list, testListGet);
	tcase_add_test(tc_list, testListFront);
	tcase_add_test(tc_list, testListBack);

	suite_add_tcase(suite, tc_list); 
    return suite;
}
