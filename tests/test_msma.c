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
#include "../src/mcsv.h"


START_TEST (testSMAInitDestruct) {
	uint64_t size = 0; 
	SimpleMovingAverage * sma = sma_init(3);
	ck_assert_ptr_nonnull(sma);

	ck_assert_int_eq(0, size);

	sma_destruct(&sma);
	ck_assert_ptr_null(sma);
}

/* For gdb
 *	p *((double*) sma->values->values)@3
 */
START_TEST (testSMAAddGet) {
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
	get_val = sma_get(sma); // (2+4+NAN)/3.0
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	value = 8;
	sma_add(sma, &value);
	get_val = sma_get(sma); // (4+NAN+8)/3.0
	is_nan = isnan(get_val);
	ck_assert_int_gt(is_nan, 0);

	value = 3.14;
	sma_add(sma, &value); // NAN, 8, 3.14
	value = 1.5; 
	sma_add(sma, &value); // 8, 3.14, 1.5
	get_val = sma_get(sma);
	expected = (8+3.14+1.5)/3.0;
	ck_assert_double_eq(expected, get_val);

	sma_destruct(&sma);
}

START_TEST (testSMAMath) {
	double value = 0;
	double get_val = 0;
	double is_nan = 0;
	const double NUM_DECIMAL_PLACES = 10.0;
	double get_val_rounded = 0;
	double value_rounded = 0;
	uint64_t num_rows = 0;
	uint64_t num_columns = 0;
	uint64_t skip_rows = 1;
	uint64_t index_row = 0;
	const uint64_t period = 5;
	const uint64_t DATA_COLUMN = 0;
	const uint64_t SMA_COLUMN = 1;
	const char DATA_FILENAME[23] = "resources/sma-nan.csv";
	const char SEPARATOR[2] = ",";	
	double ** matrix;
	SimpleMovingAverage * sma = sma_init(period);
	sma->nan_to_zero = 1;
	Table table;

	read_csv(DATA_FILENAME, SEPARATOR, &table);

	matrix = table_as_double(&table,
							 skip_rows,
							 &num_rows,
							 &num_columns);
    /*
	for (index_row=0; index_row<num_rows; index_row++)
		printf("%0.8f\t%0.8f\n", matrix[index_row][0], matrix[index_row][1]);
	*/
	for (index_row=0; index_row<num_rows; index_row++){
		value = matrix[index_row][DATA_COLUMN];
		sma_add(sma, &value);
		get_val = sma_get(sma);
		is_nan = isnan(get_val);
		value = matrix[index_row][SMA_COLUMN];
		if (is_nan){
			is_nan = isnan(value);
			if (is_nan == 0)
				printf("\n\ttestSMAMath: Mismatch NAN in the row with index %llu (SMA: %f, DATA: %f)\n", 
					   (unsigned long long int)index_row, get_val, value);
			ck_assert_int_gt(is_nan, 0);
		} else {
			value_rounded = (long long int)(value * NUM_DECIMAL_PLACES);
		   	get_val_rounded = (long long int)(get_val * NUM_DECIMAL_PLACES);
			if (value_rounded != get_val_rounded)	
			printf("\n\ttestSMAMath: Mismatch values in the row with index %llu (SMA: %f DATA: %f)\n",
					   (unsigned long long int)index_row, get_val, value);	
			ck_assert_int_eq(value, get_val);
		}
	}

	for (index_row=0; index_row<num_rows; index_row++)
		free(matrix[index_row]);
	free(matrix);
	matrix = NULL;

	table_destruct(&table);
	sma_destruct(&sma);
}

Suite* suite_msma(){
    Suite* suite = suite_create("Simple Moving Average Suite");
    TCase* tc_sma = tcase_create("SMA");

    tcase_add_test(tc_sma, testSMAInitDestruct);
	tcase_add_test(tc_sma, testSMAAddGet);
	tcase_add_test(tc_sma, testSMAMath);
	
	suite_add_tcase(suite, tc_sma); 
    return suite;
}
