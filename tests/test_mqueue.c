/* Mylibc Queue Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>

#include "test_mqueue.h"
#include "../src/mqueue.h"


START_TEST (testQueue) {
	double read = 1;
	double write = 0;
	char * str = NULL;
	StatusList status = STATUS_LIST_ERROR_MEM_ALOC;
	Queue * queue = queue_init(sizeof(double));
	ck_assert_ptr_nonnull(queue);
	ck_assert_int_eq(queue_size(queue), 0);	

	u_int64_t size = 0;
	while (read < 5){
		status = queue_insert(queue, (void*)&read);
		size++;
		read += 1.0;
		ck_assert_int_eq(TRUE, status==STATUS_LIST_SUCCESS);
		ck_assert_int_eq(queue_size(queue), size);	
	}
	ck_assert_int_eq(queue_size(queue), 4);	

	queue_front(queue, (void*)&write);
	ck_assert_double_eq(write, 1.0);	

	str = queue_str(queue, "%.1f", 3);
	ck_assert_str_eq(str, "[1.0 <- 2.0 <- 3.0 <- 4.0]\n");
	free(str);

	queue_destruct(&queue);
	ck_assert_ptr_null(queue);
}

Suite* suite_mqueue(){
    Suite* suite = suite_create("Queue Suite");
    TCase* tc_list= tcase_create("Queue");

    tcase_add_test(tc_list, testQueue);

	suite_add_tcase(suite, tc_list); 
    return suite;
}
