/* Mylibc Math Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h> 

#include "test_mmath.h"
#include "../src/mmath.h"


START_TEST (testMatrix) {
	uint8_t num_dimensions = 2;
	size_t sizes[] = {3, 3};
	size_t size_of_type = sizeof(double);
	size_t indices[] = {0, 0};
	uint8_t row;
	uint8_t col;
	double write = 0.1;
	double read = 0;

	Matrix * matrix = matrix_init(sizes, num_dimensions, size_of_type);
	ck_assert_ptr_nonnull(matrix);

	write = 0.1;
	for (row=0; row<sizes[0]; row++){
		for (col=0; col<sizes[1]; col++){
			indices[0] = row;
			indices[1] = col;
			write += 1.0;
			read = 0;
			matrix_set(matrix, indices, &write);
			matrix_get(matrix, indices, &read);
			ck_assert_double_eq(write, read);
		}
	}

	matrix_destruct(&matrix);
	ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST (testMean) {
	uint8_t ignore_nan = 0;
	uint8_t nan_to_zero = 0;
	uint64_t size = 4; 
	const double data1[] = {1.0, 1.5, 0.5, 1.0};
	double mean_val = mean(data1, size, ignore_nan, nan_to_zero);
	double expected_val = 1.0;
	ck_assert_int_eq(expected_val, mean_val);

	const double data2[] = {1.0, 1.5, NAN, 1.0};
	ignore_nan = 0;
	nan_to_zero = 0;
	mean_val = mean(data2, size, ignore_nan, nan_to_zero);
	ck_assert_double_nan(mean_val);

	const double data3[] = {1.0, 1.5, NAN, 1.0};
	ignore_nan = 1;
	nan_to_zero = 0;
	mean_val = mean(data3, size, ignore_nan, nan_to_zero);
	expected_val = 3.5/3.0;
	ck_assert_int_eq(expected_val, mean_val);

	const double data4[] = {1.0, 1.5, NAN, 1.0};
	ignore_nan = 0;
	nan_to_zero = 1;
	mean_val = mean(data4, size, ignore_nan, nan_to_zero);
	expected_val = 3.5 / 4.0;
	ck_assert_int_eq(expected_val, mean_val);
}

START_TEST (testStddev) {
	uint8_t ignore_nan = 0;
	uint64_t size = 4; 
	const double data1[] = {1.0, 1.5, 0.5, 1.0};
	double mean_val = stddev(data1, size, ignore_nan);
	double expected_val = 0.3535533905932738;
	ck_assert_double_eq_tol(expected_val, mean_val, pow(10, -16));

	const double data2[] = {1.0, 1.5, NAN, 1.0};
	ignore_nan = 0;
	mean_val = stddev(data2, size, ignore_nan);
	ck_assert_double_nan(mean_val);

	const double data3[] = {1.0, 1.5, NAN, 1.0};
	ignore_nan = 1;
	mean_val = stddev(data3, size, ignore_nan);
	expected_val = 0.23570226039551584;
	ck_assert_double_eq_tol(expected_val, mean_val, pow(10, -16));
}


Suite* suite_mmath(){
    Suite* suite = suite_create("Math Suite");
    TCase* tc_matrix = tcase_create("Matrix");
    tcase_add_test(tc_matrix, testMatrix);
	tcase_add_test(tc_matrix, testMean);
	tcase_add_test(tc_matrix, testStddev);
    suite_add_tcase(suite, tc_matrix); 
    return suite;
}
