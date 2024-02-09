/* Mylibc CSV
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "mcsv.h"
#include "mstring.h"


void table_init(Table * self, uint64_t num_rows, uint64_t num_columns){
	uint64_t index_row = 0;
	uint64_t index_column = 0;
	if (num_rows > 0 && num_columns > 0){
		self->num_rows = num_rows;
		self->num_columns = num_columns;
		self->data = (char***) malloc(sizeof(char**) * num_rows);
		if (self->data !=NULL){
			for (index_row=0; index_row<self->num_rows; index_row++){
				self->data[index_row] = (char**) malloc(sizeof(char*) * self->num_columns);
				if (self->data[index_row] != NULL){
					for (index_column=0; index_column<self->num_columns; index_column++){
						self->data[index_row][index_column] = (char*) malloc(sizeof(char)*2);
						sprintf(self->data[index_row][index_column], "");
					}
				} else {
					self->num_rows = 0;
					self->num_columns = 0;
					break;
				}
			}
		} else {
			self->num_rows = 0;
			self->num_columns = 0;
		}
	}
}

void table_destruct(Table * self){
	uint64_t index_row = 0;
	uint64_t index_column = 0;
	if (self != NULL && self->data != NULL){
		for (index_row=0; index_row<self->num_rows; index_row++){
			if (self->data[index_row] != NULL){
				for (index_column=0; index_column<self->num_columns; index_column++)
					if (self->data[index_row][index_column] != NULL)
						free(self->data[index_row][index_column]);
				free(self->data[index_row]);
			}
		}
		free(self->data);
		self->data = NULL;
		self->num_rows = 0;
		self->num_columns = 0;
	}
}

void table_print(const Table * table){
	uint64_t index_row = 0;
	uint64_t index_column = 0;
	if (table != NULL){
		for(index_row = 0; index_row<table->num_rows; index_row++){
			for (index_column=0; index_column<table->num_columns; index_column++){
				printf("%s", table->data[index_row][index_column]);
				if (index_column < table->num_columns-1)
					printf(" ");
			}
			if (index_row < table->num_rows-1)
				printf("\n");
		}
	}
}

StatusCSV read_csv(const char * filename, 
		const char * separator,
		Table * table){
	unsigned char counting_columns = 0;
	uint64_t num_columns = 0;
	uint64_t num_rows = 0;
	uint64_t index_row = 0;
	uint64_t index_column = 0;
	uint64_t split_size = 0;
	long file_size = 0;
	char * buffer = NULL;
	char ** split = NULL;	
	StatusCSV status = STATUS_CSV_SUCCESS;
	FILE * file = NULL;

	if (filename == NULL)
		status = STATUS_CSV_ERROR_INVALID_FILENAME;

	if (status == STATUS_CSV_SUCCESS){
		file = fopen(filename, "r");
		if (!file)
			status = STATUS_CSV_ERROR_OPENING_FILE;
	}

	if (status == STATUS_CSV_SUCCESS){
		if (fseek(file, 0, SEEK_END) != 0){
			status = STATUS_CSV_ERROR_READING_FILE;
			fclose(file);
		}
	}

	if (status == STATUS_CSV_SUCCESS){
		file_size = ftell(file) + 1;
		if (file_size == -1) {
			status = STATUS_CSV_ERROR_READING_FILE;
			fclose(file);
		}
		rewind (file);
	}

	if (status == STATUS_CSV_SUCCESS){
		buffer = (char*) malloc(file_size);
		fread(buffer, 1, file_size, file);
		num_rows = string_count_char(buffer, '\n'); 
		rewind(file);	
		index_row = 0;
		counting_columns = 1;
		while (fgets(buffer, file_size, file)){
			/* If blank line, just skip. */
			if (strcmp(buffer, "") != 0){
				split = string_split(buffer, separator, &split_size);
				if (counting_columns){
					counting_columns = 0;
					num_columns = split_size;
					table_init(table, num_rows, num_columns);
				}
				/* Stop Processing if the number of columns is not the same as the line 0
				   Change the status to CSV Malformed. */
				if (split_size != table->num_columns){
					status = STATUS_CSV_MALFORMED;
					break;
				}

				for (index_column=0; index_column<split_size; index_column++){
					free(table->data[index_row][index_column]);
					table->data[index_row][index_column] = string_remove(split[index_column], " \n");
					free(split[index_column]);
				}
				free(split);
				split = NULL;
				index_row++;
			}
		}
	}

	if (status == STATUS_CSV_SUCCESS)
		fclose(file);
	if (buffer != NULL)
		free(buffer);
	return status;
}

double ** table_as_double(const Table * table,
						  uint64_t skip_rows,
						  uint64_t * num_rows,
						  uint64_t * num_columns){
	uint64_t index_row = 0;
	uint64_t index_column = 0;
	double number = 0;
	double ** matrix = NULL;
	char * endptr = NULL;
	if (   table != NULL
		&& table->data != NULL
		&& table->num_rows > 0
		&& table->num_columns > 0
		&& (table->num_rows - skip_rows) > 0) {
		matrix = (double**) malloc(sizeof(double*) * (table->num_rows - skip_rows));
		for (index_row=0; index_row < (table->num_rows-skip_rows); index_row++)
			matrix[index_row] = (double*) malloc (sizeof(double) * table->num_columns);
		if (num_rows != NULL)
			*num_rows = table->num_rows - skip_rows;
		if (num_columns != NULL)
			*num_columns = table->num_columns;
		for (index_row=skip_rows; index_row<table->num_rows; index_row++){
			for (index_column=0; index_column<table->num_columns; index_column++){
				number = strtod(table->data[index_row][index_column], &endptr);
				if (*endptr != '\0') {
					number = NAN;
				}
				matrix[index_row-skip_rows][index_column] = number;
			}
		}
	}
	return matrix;
}

