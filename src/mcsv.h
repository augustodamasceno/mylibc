/* Mylibc CSV
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MCSV_H
#define _MCSV_H

#define TRUE 1
#define FALSE 0

#include <stdint.h>

typedef struct {
	char *** data;
	uint64_t num_rows;
	uint64_t num_columns;
} Table;


typedef enum {
	STATUS_CSV_SUCCESS,
	STATUS_CSV_ERROR_OPENING_FILE,
	STATUS_CSV_ERROR_READING_FILE,
	STATUS_CSV_ERROR_INVALID_FILENAME,
	STATUS_CSV_MALFORMED
} StatusCSV;

StatusCSV read_csv(char * filename, 
				   char * separator,
				   Table * table);
void table_init(Table * self, uint64_t num_rows, uint64_t num_columns);
void table_destruct(Table * self);
void table_print(const Table * table);
double ** table_as_double(const Table * table,
						  uint64_t skip_rows,
						  uint64_t * num_rows,
						  uint64_t * num_columns);

#endif /* _MCSV_H  */

