/* Mylibc Moving Correlation Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
#include <math.h>

#include "../src/mmcorr.h"
#include "test_mmcorr.h"


START_TEST (testInitDestruct) {
	uint64_t size = 2; 
	MovingCorrelation * mcorr = mcorr_init(size);
	ck_assert_ptr_nonnull(mcorr);

	ck_assert_int_eq(size, mcorr->period);

	mcorr_destruct(&mcorr);
	ck_assert_ptr_null(mcorr);
}

START_TEST (testAddGet) {
	double value = 0;
	double get_val = 0;
	double is_nan = 0;
	uint64_t period = 2;
	MovingCorrelation * mcorr = mcorr_init(period);

	uint64_t max_size = period;
	StaticQueue * second_var = squeue_init(sizeof(double), max_size);
	value = 1;
	squeue_insert(second_var, (void*)&value);
	value = 2;
	squeue_insert(second_var, (void*)&value);

	/* Size < Period */
	value = 1.1;
	mcorr_add(mcorr, &value);
	get_val = mcorr_get(mcorr, second_var);
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	/* mcoor values are [1.1, 2.2]
	   queue values are [1.0, 2.0] */
	value = 2.2;
	mcorr_add(mcorr, &value);
	get_val = mcorr_get(mcorr, second_var);
	ck_assert_double_eq(1, get_val);

	/* mcoor values are [1.0, 1.0]
	   queue values are [1.0, 2.0] */
	value = 1.0;
	mcorr_add(mcorr, &value);
	value = 1.0;
	mcorr_add(mcorr, &value);
	get_val = mcorr_get(mcorr, second_var);
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	/* mcoor values are [4.0, 5.0]
	   queue values are [1.0, 2.0] */
	value = 4.0;
	mcorr_add(mcorr, &value);
	value = 5.0;
	mcorr_add(mcorr, &value);
	get_val = mcorr_get(mcorr, second_var);
	ck_assert_double_eq(1, get_val);

	/* mcoor values are [5.0, 4.0]
	   queue values are [1.0, 2.0] */
	value = 4.0;
	mcorr_add(mcorr, &value);
	get_val = mcorr_get(mcorr, second_var);
	ck_assert_double_eq(-1, get_val);

	squeue_destruct(&second_var);
	mcorr_destruct(&mcorr);
}

Suite* suite_mmcorr(){
    Suite* suite = suite_create("Moving Correlation Suite");
    TCase* tc_mcorr = tcase_create("MCORR");

    tcase_add_test(tc_mcorr, testInitDestruct);
	tcase_add_test(tc_mcorr, testAddGet);

	suite_add_tcase(suite, tc_mcorr); 
    return suite;
}
