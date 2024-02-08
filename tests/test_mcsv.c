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

Suite* suite_mcsv(){
    Suite* suite = suite_create("CSV Suite");
    TCase* tc_csv = tcase_create("CSV");

	tcase_add_test(tc_csv, testTable);
	tcase_add_test(tc_csv, testReadCSV);

	suite_add_tcase(suite, tc_csv); 
    return suite;
}

