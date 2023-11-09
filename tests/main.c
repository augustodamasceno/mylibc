/* Mylibc Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <stdio.h>

#include <check.h>

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
			matrix_set(matrix, indices, &write, sizeof(double));
			matrix_get(matrix, indices, &read, sizeof(double));
			ck_assert_double_eq(write, read);
		}
	}

	matrix_destruct(&matrix);
	ck_assert_ptr_null(matrix);
}
END_TEST


int main()
{
    Suite *s = suite_create("Test suite for Math");

    TCase *tcCore = tcase_create("Core");
    tcase_add_test(tcCore, testMatrix);
    suite_add_tcase(s, tcCore);
    SRunner *runner = srunner_create(s);
    srunner_set_fork_status (runner, CK_NOFORK);
    srunner_run_all(runner, CK_VERBOSE);

    int num_tests = srunner_ntests_run(runner);
    int num_failures = srunner_ntests_failed(runner);
    int num_success = num_tests - num_failures;

    srunner_free(runner);

    printf("Sucess: %d Failures: %d\n", num_success, num_failures);
	return 0;
} 
