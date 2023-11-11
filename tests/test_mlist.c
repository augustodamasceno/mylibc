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


START_TEST (testList) {
	List * list = list_init(sizeof(double));
	ck_assert_ptr_nonnull(list);

	ck_assert_int_eq(0, list->size);

	double read = 100;
	list_insert_front(list, (void *)&read);
	ck_assert_int_eq(1, list->size);

	char * list_str = list_str_double_format(list);
	printf("%s", list_str);
	free(list_str);

	list_destruct(&list);
	ck_assert_ptr_null(list);
}

Suite* suite_mlist(){
    Suite* suite = suite_create("List Suite");
    TCase* tc_list= tcase_create("List");

    tcase_add_test(tc_list, testList);
    
	suite_add_tcase(suite, tc_list); 
    return suite;
}
