/* Mylibc Moving Correlation Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../src/mmcorr.h"
#include "../src/msqueue.h"
#include "../src/mcsv.h"
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

START_TEST (testMCORRMath) {	
	const double NUM_DECIMAL_PLACES = 10.0;
	const uint64_t period = 5;
	const uint64_t DATA_A_COLUMN = 0;
	const uint64_t DATA_B_COLUMN = 1;
	const uint64_t MCORR_COLUMN = 2;
	const char DATA_FILENAME[23] = "resources/mcorr.csv";
	const char SEPARATOR[2] = ",";	
	uint64_t num_rows = 0;
	uint64_t num_columns = 0;
	uint64_t skip_rows = 1;
	uint64_t index_row = 0;
	double data_val = 0;
	double mcorr_val = 0;
	double mcorr_val_rounded = 0;
	double data_val_rounded = 0;
	double round_mult = pow(10, NUM_DECIMAL_PLACES);
	double ** matrix;
	MovingCorrelation * mcorr = mcorr_init(period);
	StaticQueue * second_var = squeue_init(sizeof(double), period);
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
	for(index_row=0; index_row<period; index_row++){
		data_val = matrix[index_row][DATA_A_COLUMN];
		mcorr_add(mcorr, (void*)&data_val);
		data_val = matrix[index_row][DATA_B_COLUMN];
		squeue_insert(second_var, (void*)&data_val);
	}
	for (index_row=period; index_row<num_rows; index_row++){
		mcorr_val = mcorr_get(mcorr, second_var);
		data_val = matrix[index_row-period][MCORR_COLUMN];

		data_val_rounded = (long long int)(data_val * round_mult);
		mcorr_val_rounded = (long long int)(mcorr_val * round_mult);
		data_val_rounded /= round_mult;
		mcorr_val_rounded /= round_mult;
		
		if (data_val_rounded != mcorr_val_rounded)
			printf("\n\ttestMCORRMath: Mismatch values in the row with index %llu (MCORR: %.12f DATA: %.12f)\n",
				   (unsigned long long int)index_row, mcorr_val, data_val);	
		ck_assert_double_eq(data_val_rounded, mcorr_val_rounded);
		
		data_val = matrix[index_row][DATA_A_COLUMN];
		mcorr_add(mcorr, (void*)&data_val);
		data_val = matrix[index_row][DATA_B_COLUMN];
		squeue_insert(second_var, (void*)&data_val);
	}

	for (index_row=0; index_row<num_rows; index_row++)
		free(matrix[index_row]);
	free(matrix);
	matrix = NULL;

	table_destruct(&table);
	mcorr_destruct(&mcorr);
	squeue_destruct(&second_var);
}
	
Suite* suite_mmcorr(){
    Suite* suite = suite_create("Moving Correlation Suite");
    TCase* tc_mcorr = tcase_create("MCORR");

    tcase_add_test(tc_mcorr, testInitDestruct);
	tcase_add_test(tc_mcorr, testAddGet);
	tcase_add_test(tc_mcorr, testMCORRMath);

	suite_add_tcase(suite, tc_mcorr); 
    return suite;
}
