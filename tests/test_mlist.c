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


START_TEST (testInitDestruct) {
	List * list = list_init(sizeof(double));
	ck_assert_ptr_nonnull(list);

	ck_assert_int_eq(0, list->size);
	ck_assert_int_eq(sizeof(double), list->size_of_type);
	ck_assert_ptr_null(list->head);
	ck_assert_ptr_null(list->tail);

	list_destruct(&list);
	ck_assert_ptr_null(list);
}

START_TEST (testInsertFront) {
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
	ck_assert_str_eq(str, "[100.0]\n");
	free(str);

	read = 0.123;
	status = list_insert_front(list, (void *)&read);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[0.123,100.000]\n");
	free(str);

	read = -456;
	status = list_insert_front(list, (void *)&read);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[-456.000,0.123,100.000]\n");
	free(str);

	list_destruct(&list);
}

START_TEST (testInsertBack) {
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
	ck_assert_str_eq(str, "[100.0]\n");
	free(str);

	read = 0.123;
	status = list_insert_back(list, (void *)&read);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[100.000,0.123]\n");
	free(str);

	read = -456;
	status = list_insert_back(list, (void *)&read);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);

	str = list_str(list, "%.3f", 5);
	ck_assert_str_eq(str, "[100.000,0.123,-456.000]\n");
	free(str);

	list_destruct(&list);
}

START_TEST (testInsertAt) {
	char * str = NULL;
	int read = -1;
	u_int64_t index = 0;
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
	ck_assert_str_eq(str, "[1]\n");
	free(str);

	/* Index equal to the size of the list. */
	read = 2;
	index = 1;
	status = list_insert_at(list, (void *)&read, index);
	ck_assert_int_eq(2, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[1,2]\n");
	free(str);

	/* Index in the middle of the list. */
	read = 3;
	status = list_insert_at(list, (void *)&read, 1);
	ck_assert_int_eq(3, list->size);
	ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
	str = list_str(list, "%d", 1);
	ck_assert_str_eq(str, "[1,3,2]\n");
	free(str);



	list_destruct(&list);
}

Suite* suite_mlist(){
    Suite* suite = suite_create("List Suite");
    TCase* tc_list= tcase_create("List");

    tcase_add_test(tc_list, testInitDestruct);
	tcase_add_test(tc_list, testInsertFront);
    tcase_add_test(tc_list, testInsertBack);
	tcase_add_test(tc_list, testInsertAt);

	suite_add_tcase(suite, tc_list); 
    return suite;
}