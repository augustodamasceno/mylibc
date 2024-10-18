/* Mylibc Math
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include "mmath.h"


Matrix * matrix_init(size_t * sizes, uint8_t num_dimensions, size_t size_of_type){
	Matrix * matrix = (Matrix *) malloc(sizeof(Matrix));
	matrix->sizes = (size_t*) malloc(size_of_type * num_dimensions);

	if (matrix->sizes) {
		size_t size = size_of_type;
		uint8_t dimension_idx;
		uint8_t sizes_idx;
		for (sizes_idx=0; sizes_idx<num_dimensions; sizes_idx++)
			matrix->sizes[sizes_idx] = sizes[sizes_idx];

		matrix->num_dimensions = num_dimensions;
		matrix->size_of_type = size_of_type;

		for(dimension_idx=0; dimension_idx<matrix->num_dimensions; dimension_idx++)
			size *= matrix->sizes[dimension_idx];
		matrix->data = malloc(size);

		if (matrix->data == NULL){
			free(matrix->sizes);
			matrix->sizes = NULL;
			free(matrix);
			matrix = NULL;
		}
	}

	return matrix;
}

void matrix_destruct(Matrix ** self){
	free((*self)->data);
	(*self)->data = NULL;
	free((*self)->sizes);
	(*self)->sizes = NULL; 
	(*self)->num_dimensions = 0;
	(*self)->size_of_type = 0;
	free(*self);
	*self = NULL;
}

size_t matrix_offset(Matrix * self, size_t * indices){
	size_t offset = 0;
    size_t last_dimension_offset = 1;
	uint8_t dimension_idx;
	for(dimension_idx=0; dimension_idx<self->num_dimensions; dimension_idx++){
        offset += indices[dimension_idx] * last_dimension_offset;
        last_dimension_offset *= self->sizes[dimension_idx];
    }
	return offset;
}

void matrix_get(Matrix * self, size_t * indices, void * write_location){
	size_t offset = matrix_offset(self, indices);
    char * data_location = (char*) self->data + offset * self->size_of_type;
    memcpy(write_location, data_location, self->size_of_type);
}

void matrix_set(Matrix * self, size_t * indices, void * read_location){
	size_t offset = matrix_offset(self, indices);
    char * data_location = (char*) self->data + offset * self->size_of_type;
    memcpy(data_location, read_location, self->size_of_type);
}

/* Normalize data in a vector */
void normalize(double * vec, uint64_t size)
{
	uint64_t i;
	double offset = 0;

	/* Find the minor value */
	for(i=0; i<size; i++)
	{
		if ( vec[i] < offset )
			offset = vec[i];
	}
	
	/* Shift the vector to the positive side and find the maximum */
	offset *= -1;
	vec[0] += offset;
	double max = vec[0];
	for(i=1; i<size; i++)
	{
		vec[i] += offset;
		if(vec[i] > max)
			max = vec[i];
	}

	/* Normalize data */
	for(i=0; i<size; i++)
		vec[i] /= max;
}

/* Get the continuos value from a quantized binary sample */
double getQuantizationLevel(uint64_t binary, uint64_t nbits, double minValue, double maxValue)
{
	int i;
	uint64_t getbit = 1;
	double sum = 0;
	/* Calc from fractional part in fixed point data representation */
	for(i=(-1*nbits); i<=-1; i++)
	{
		if (binary & getbit)
			sum += pow(2.0, (double) i);
		
		getbit = getbit<<1;
	}

	return sum*(maxValue-minValue)+minValue;
}

/* Vector Random Permutation */
void permutation(int * vec, uint64_t size)
{
	uint64_t i;
	int swap;
	int r;
	srand (time(NULL));	/* Initialize random seed */
	for(i=0; i<size; i++)
	{
		r = rand() % size;
		swap = vec[i];
		vec[i] = vec[r];
		vec[r] = swap;
	}
}


double mean(const double * data, uint64_t size, uint8_t ignore_nan, uint8_t nan_to_zero) {
	int i = 0;
	uint64_t nan_counter = 0;
	double sum = 0.0;
	double result = 0.0;
	double data_size = (double) size;

	for (i=0; i<size; i++){
		if (isnan(data[i]) == 0)
			sum += data[i];
		else
			nan_counter++;
	}

	/* Case ignore_nan - nan_to_zero is not used */
	if (ignore_nan)
		data_size -= (double) nan_counter;
	/* Case nan_to_zero disabled - do not accept NAN 
	 * Case nan_to_zero enabled - do nothing (NAN already converted to zero) */
	else if ((nan_to_zero == 0) && (nan_counter > 0) )
		data_size = 0;

	if (data_size == 0)
		result = NAN;
	else
		result = sum / data_size;

	return result;
}

double stddev(const double * data, uint64_t size, uint8_t ignore_nan) {
	int i = 0; 
	uint8_t nan_to_zero = 0;
	uint64_t nan_counter = 0;
	double mean_val = mean(data, size, ignore_nan, nan_to_zero);
	double sum_squared_diff = 0.0;
	double result = NAN;
	double data_size = (double) size;

	if (isnan(mean_val) == 0){
		for (int i=0; i<size; i++){
			if (isnan(data[i]) == 0){
				sum_squared_diff += (data[i] - mean_val) 
					  	  		  * (data[i] - mean_val);
			} else
				nan_counter++;
		}
	} else
		data_size = 0.0;

	if (ignore_nan)
		data_size -= (double) nan_counter;

	if (data_size == 0.0)
		result = NAN;
	else
		result = sqrt(sum_squared_diff / data_size);

	return result;
}

