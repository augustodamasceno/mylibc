/* Mylibc CSV Tests
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
#include <stdint.h>

#include "test_mcsv.h"
#include "../src/mcsv.h"



START_TEST (testTable) {
	uint64_t num_rows = 2;
	uint64_t num_columns = 3;
	uint64_t expected = 0;
	Table table;
	table_init(&table, num_rows, num_columns);

	expected = 2;
	ck_assert_int_eq(expected, num_rows);
	expected = 3;
	ck_assert_int_eq(expected, num_columns);

	ck_assert_str_eq(table.data[0][0], "");
	ck_assert_str_eq(table.data[0][1], "");
	ck_assert_str_eq(table.data[0][2], "");
	ck_assert_str_eq(table.data[1][0], "");
	ck_assert_str_eq(table.data[1][1], "");
	ck_assert_str_eq(table.data[1][2], "");

	table_destruct(&table);
}

START_TEST (testReadCSV) {
	char filename[23] = "resources/sma-nan.csv";
	char separator[2] = ",";
	Table table;
	StatusCSV status = read_csv(filename,
								separator,
								&table);
	ck_assert_str_eq(table.data[0][0], "Data");
	ck_assert_str_eq(table.data[0][1], "SMA");	
	ck_assert_int_eq(status, STATUS_CSV_SUCCESS);

	table_destruct(&table);
}

START_TEST (testTableAsDouble) {
	char filename[23] = "resources/sma-nan.csv";
	char separator[2] = ",";
	uint64_t skip_rows = 98;
	uint64_t index_row = 0;
	double ** matrix = NULL;
	uint64_t num_rows = 0;
	uint64_t num_columns = 0;
	Table table;
	StatusCSV status = read_csv(filename, separator, &table);
	ck_assert_int_eq(status, STATUS_CSV_SUCCESS);

	matrix = table_as_double(&table, skip_rows, &num_rows, &num_columns);
	ck_assert_double_eq(0.427541, matrix[0][0]);
	ck_assert_double_eq(0.555263, matrix[0][1]);
	ck_assert_double_eq(0.025419, matrix[1][0]);
	ck_assert_double_eq(0.448091, matrix[1][1]);
	ck_assert_double_eq(0.107891, matrix[2][0]);
	ck_assert_double_eq(0.315476, matrix[2][1]);

	for (index_row=0; index_row<num_rows; index_row++)
		free(matrix[index_row]);
	free(matrix);
	matrix = NULL;

	table_destruct(&table);
}

Suite* suite_mcsv(){
    Suite* suite = suite_create("CSV Suite");
    TCase* tc_csv = tcase_create("CSV");

	tcase_add_test(tc_csv, testTable);
	tcase_add_test(tc_csv, testReadCSV);
	tcase_add_test(tc_csv, testTableAsDouble);
	
	suite_add_tcase(suite, tc_csv); 
    return suite;
}

