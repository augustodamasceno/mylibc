/* Mylibc Simple Moving Average Tests
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

#include "../src/msma.h"
#include "test_msma.h"


START_TEST (testInitDestruct) {
	uint64_t size = 0; 
	SimpleMovingAverage * sma = sma_init(3);
	ck_assert_ptr_nonnull(sma);

	ck_assert_int_eq(0, size);

	sma_destruct(&sma);
	ck_assert_ptr_null(sma);
}

START_TEST (testAddGet) {
	double value = 0;
	double get_val = 0;
	double is_nan = 0;
	double expected = 0;
	SimpleMovingAverage * sma = sma_init(3);

	value = 1;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	value = 2;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	value = 4;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	expected = (1+2+4)/3.0;
	ck_assert_double_eq(expected, get_val);

	value = NAN;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	ck_assert_double_eq(expected, get_val);

	value = 8;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	expected = (2+4+8)/3.0;
	ck_assert_double_eq(expected, get_val);

	value = NAN;
	sma_add(sma, &value);
	get_val = sma_get(sma);
	ck_assert_double_eq(expected, get_val);


	sma_destruct(&sma);
}



Suite* suite_msma(){
    Suite* suite = suite_create("Simple Moving Average Suite");
    TCase* tc_sma = tcase_create("SMA");

    tcase_add_test(tc_sma, testInitDestruct);
	tcase_add_test(tc_sma, testAddGet);

	suite_add_tcase(suite, tc_sma); 
    return suite;
}
