/* Mylibc Static Queue Tests
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "test_msqueue.h"
#include "../src/msqueue.h"


START_TEST (testSQueue) {	
	uint64_t max_size = 4;
	double read = 0;
	double write = 0;
	double sum = 0;
	double expected_value = 0;
	uint64_t expected_index = 0;
	uint64_t expected_size = 0;
	char * str = NULL;

	StaticQueue * queue = squeue_init(sizeof(double), max_size);
	ck_assert_ptr_nonnull(queue);
	ck_assert_int_eq(queue->size, 0);
	ck_assert_int_eq(-1, queue->front);
	ck_assert_int_eq(-1, queue->back);	

	read = 1;
	squeue_insert(queue, (void*)&read);
	expected_size = 1;
	ck_assert_int_eq(expected_size, queue->size);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->front);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->back);
	squeue_front(queue, (void*)&write);	
	expected_value = 1.0;
	ck_assert_double_eq(expected_value, write);

	read = 2;
	squeue_insert(queue, (void*)&read);
	expected_size = 2;
	ck_assert_int_eq(expected_size, queue->size);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->front);
	expected_index = 1;
	ck_assert_int_eq(expected_index, queue->back);
	squeue_front(queue, (void*)&write);	
	expected_value = 1.0;
	ck_assert_double_eq(expected_value, write);

	read = 3;
	squeue_insert(queue, (void*)&read);
	expected_size = 3;
	ck_assert_int_eq(expected_size, queue->size);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->front);
	expected_index = 2;
	ck_assert_int_eq(expected_index, queue->back);
	squeue_front(queue, (void*)&write);	
	expected_value = 1.0;
	ck_assert_double_eq(expected_value, write);
	
	read = 4;
	squeue_insert(queue, (void*)&read);
	expected_size = 4;
	ck_assert_int_eq(expected_size, queue->size);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->front);
	expected_index = 3;
	ck_assert_int_eq(expected_index, queue->back);
	squeue_front(queue, (void*)&write);	
	expected_value = 1.0;
	ck_assert_double_eq(expected_value, write);

	str = squeue_str(queue, "%.1f", 3);
	ck_assert_str_eq(str, "[1.0 <- 2.0 <- 3.0 <- 4.0]");
	free(str);

	read = 5;
	squeue_insert(queue, (void*)&read);
	expected_size = 4;
	ck_assert_int_eq(expected_size, queue->size);
	expected_index = 1;
	ck_assert_int_eq(expected_index, queue->front);
	expected_index = 0;
	ck_assert_int_eq(expected_index, queue->back);
	squeue_front(queue, (void*)&write);	
	expected_value = 2.0;
	ck_assert_double_eq(expected_value, write);

	/* Add until 10 and check if only the last 'max_values' are kept in the queue. */
	while(read < 11){
		squeue_insert(queue, (void*)&read);
		read += 1.0;
	}

	str = squeue_str(queue, "%.2f", 5);
	ck_assert_str_eq(str, "[7.00 <- 8.00 <- 9.00 <- 10.00]");
	free(str);

	sum = squeue_sum_double(queue);
	expected_value = 34;
	ck_assert_double_eq(expected_value, sum);

	read = NAN;
	squeue_insert(queue, (void*)&read);
	sum = squeue_sum_double(queue);
	expected_value = 1;
	ck_assert_double_eq(expected_value, isnan(sum) != 0);

	sum = squeue_sumnan_double(queue);
	expected_value = 27;
	ck_assert_double_eq(expected_value, sum);

	/* After remove 9, 10, NAN */
	squeue_remove(queue);
	expected_size = 3;
	ck_assert_int_eq(expected_size, queue->size);
	squeue_front(queue, (void*)&write);	
	expected_value = 9.0;
	ck_assert_double_eq(expected_value, write);
	
	/* After remove 10, NAN */
	squeue_remove(queue);
	expected_size = 2;
	ck_assert_int_eq(expected_size, queue->size);
	squeue_front(queue, (void*)&write);	
	expected_value = 10.0;
	ck_assert_double_eq(expected_value, write);
	
	/* After remove NAN */
	squeue_remove(queue);
	expected_size = 1;
	ck_assert_int_eq(expected_size, queue->size);
	squeue_front(queue, (void*)&write);	
	expected_value = 1;
	ck_assert_double_eq(expected_value, isnan(write) != 0);

	/* After remove empty queue */
	squeue_remove(queue);
	expected_size = 0;
	ck_assert_int_eq(expected_size, queue->size);
	squeue_front(queue, (void*)&write);	
	expected_value = 1;
	ck_assert_double_eq(expected_value, isnan(write) != 0);

	/* After remove empty queue */
	squeue_remove(queue);
	expected_size = 0;
	ck_assert_int_eq(expected_size, queue->size);
	write = 100.0;
	squeue_front(queue, (void*)&write);	
	expected_value = 100.0;
	ck_assert_double_eq(expected_value, write);
	
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

