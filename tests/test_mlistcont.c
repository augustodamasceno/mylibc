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

#include "test_mlistcont.h"
#include "../src/mlistcont.h"


START_TEST (testListContInitDestruct) {
	size_t size_of_type = sizeof(double);
	size_t capacity = 1;
	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	ck_assert_ptr_nonnull(list.data);

	ck_assert_int_eq(0, list.size);
	ck_assert_int_eq(sizeof(double), list.size_of_type);
	ck_assert_int_eq(2, list.capacity); /* The next even number of 1 */
	list_cont_destruct(&list);
	ck_assert_ptr_null(list.data);
	ck_assert_int_eq(0, list.size);
	ck_assert_int_eq(0, list.capacity);
	ck_assert_int_eq(0, list.size_of_type);
}

START_TEST (testListContInsert) {
	char * str = NULL;
	double read = -1;
	size_t size_of_type = sizeof(double);
	size_t capacity = 2;

	StatusListCont status = STATUS_LISTCONT_SUCCESS;

	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	ck_assert_ptr_nonnull(&list);

	read = 100;
	status = list_cont_insert(&list, (void *)&read);
	ck_assert_int_eq(1, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);

	str = list_cont_str(&list, "%.1f", 5);
	ck_assert_str_eq(str, "[100.0]");
	free(str);

	read = 0.123;
	status = list_cont_insert(&list, (void *)&read);
	ck_assert_int_eq(2, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);

	str = list_cont_str(&list, "%.3f", 5);
	ck_assert_str_eq(str, "[100.000,0.123]");
	free(str);

	read = -456.0;
	status = list_cont_insert(&list, (void *)&read);
	ck_assert_int_eq(3, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);

	str = list_cont_str(&list, "%.3f", 8);
	ck_assert_str_eq(str, "[100.000,0.123,-456.000]");
	free(str);

	list_cont_destruct(&list);
}

START_TEST (testListContRemove) {
	char * str = NULL;
	double read = -1;
	size_t size_of_type = sizeof(double);
	size_t capacity = 2;
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	
	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	read = 100;
	status = list_cont_insert(&list, (void *)&read);
	read = 0.123;
	status = list_cont_insert(&list, (void *)&read);
	read = -456.0;
	status = list_cont_insert(&list, (void *)&read);

	status = list_cont_remove(&list);
	str = list_cont_str(&list, "%.3f", 8);
	ck_assert_int_eq(2, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_str_eq(str, "[100.000,0.123]");
	free(str);

	status = list_cont_remove(&list);
	str = list_cont_str(&list, "%.3f", 8);
	ck_assert_int_eq(1, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_str_eq(str, "[100.000]");
	free(str);

	status = list_cont_remove(&list);
	str = list_cont_str(&list, "%.3f", 8);
	ck_assert_int_eq(0, list.size);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_str_eq(str, "[]");
	free(str);

	status = list_cont_remove(&list);
	str = list_cont_str(&list, "%.3f", 8);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_EMPTY_LIST);
	free(str);
	
	list_cont_destruct(&list);
}

START_TEST (testListContClear) {
	char * str = NULL;
	double read = -1;
	size_t size_of_type = sizeof(double);
	size_t capacity = 2;
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	
	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	read = 100;
	status = list_cont_insert(&list, (void *)&read);
	read = 0.123;
	status = list_cont_insert(&list, (void *)&read);
	read = -456.0;
	status = list_cont_insert(&list, (void *)&read);

	list_cont_clear(&list);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	
	str = list_cont_str(&list, "%.3f", 8);	
	ck_assert_str_eq(str, "[]");
	free(str);
	
	list_cont_destruct(&list);
}

START_TEST (testListContGet) {
	double read = -1;
	double write = -1;
	size_t size_of_type = sizeof(double);
	size_t capacity = 2;
	uint64_t index = 0;
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	
	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	read = 100;
	status = list_cont_insert(&list, (void *)&read);
	read = 0.123;
	status = list_cont_insert(&list, (void *)&read);
	read = -456.0;
	status = list_cont_insert(&list, (void *)&read);

	index = 0;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(100.0, write);
	
	index = 1;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(0.123, write);
	
	index = 2;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(-456.0, write);
	
	list_cont_destruct(&list);
}

START_TEST (testListContSet) {
double read = -1;
	double write = -1;
	size_t size_of_type = sizeof(double);
	size_t capacity = 2;
	uint64_t index = 0;
	StatusListCont status = STATUS_LISTCONT_SUCCESS;
	
	ListCont list = list_cont_init_capacity(size_of_type, capacity);
	read = 100;
	status = list_cont_insert(&list, (void *)&read);
	read = 0.123;
	status = list_cont_insert(&list, (void *)&read);
	read = -456.0;
	status = list_cont_insert(&list, (void *)&read);

	index = 0;
	read = 98.756;
	status = list_cont_set(&list, (void *)&read, index);

	index = 1;
	read = -10.01;
	status = list_cont_set(&list, (void *)&read, index);

	index = 2;
	read = 0.38;
	status = list_cont_set(&list, (void *)&read, index);

	index = 0;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(98.756, write);
	
	index = 1;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(-10.01, write);
	
	index = 2;
	status = list_cont_get(&list, (void *)&write, index);
	ck_assert_int_eq(1, status==STATUS_LISTCONT_SUCCESS);
	ck_assert_double_eq(0.38, write);
	
	list_cont_destruct(&list);
}

Suite* suite_mlist_cont(){
    Suite* suite = suite_create("Contiguous Cache-Friendly List Suite");
    TCase* tc_list_cont = tcase_create("Contiguous Cache-Friendly List");

    tcase_add_test(tc_list_cont, testListContInitDestruct);
	tcase_add_test(tc_list_cont, testListContInsert);
	tcase_add_test(tc_list_cont, testListContRemove);
	tcase_add_test(tc_list_cont, testListContClear);
	tcase_add_test(tc_list_cont, testListContGet);
	tcase_add_test(tc_list_cont, testListContSet);

	suite_add_tcase(suite, tc_list_cont); 
    return suite;
}

