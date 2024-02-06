/* Mylibc Static Queue Tests
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>

#include "test_msqueue.h"
#include "../src/msqueue.h"


START_TEST (testSQueue) {
	double read = 1;
	double write = 0;
	char * str = NULL;
	StaticQueue * queue = squeue_init(sizeof(double), 5);
	ck_assert_ptr_nonnull(queue);
	ck_assert_int_eq(queue->size, 0);	

	uint64_t size = 0;
	while (read < 5){
		squeue_insert(queue, (void*)&read);
		size++;
		read += 1.0;
		ck_assert_int_eq(queue->size, size);	
	}
	squeue_front(queue, (void*)&write);
	ck_assert_double_eq(write, 1.0);	

	str = squeue_str(queue, "%.1f", 3);
	ck_assert_str_eq(str, "[1.0 <- 2.0 <- 3.0 <- 4.0]");
	free(str);

	squeue_destruct(&queue);
	ck_assert_ptr_null(queue);
}

Suite* suite_msqueue(){
    Suite* suite = suite_create("Static Queue Suite");
    TCase* tc_squeue = tcase_create("Static Queue");

    tcase_add_test(tc_squeue, testSQueue);

	suite_add_tcase(suite, tc_squeue); 
    return suite;
}

