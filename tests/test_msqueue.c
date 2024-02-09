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
	uint64_t max_size = 4;
	double read = 1;
	double write = 0;
	double sum = 0;
	double expected = 0;
	char * str = NULL;
	StaticQueue * queue = squeue_init(sizeof(double), max_size);
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

	/* Add until 10 and check if only the last 'max_values' are kept in the queue. */
	while(read < 11){
		squeue_insert(queue, (void*)&read);
		read += 1.0;
	}

	str = squeue_str(queue, "%.2f", 5);
	ck_assert_str_eq(str, "[7.00 <- 8.00 <- 9.00 <- 10.00]");
	free(str);

	sum = squeue_sum_double(queue);
	expected = 34;
	ck_assert_double_eq(expected, sum);

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

