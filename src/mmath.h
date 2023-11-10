/* Mylibc Math
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MMATH_H
#define _MMATH_H

/* Integer Types */
#include <stdint.h>
/* srand, rand, malloc, free */
#include <stdlib.h>
/* pow */
#include <math.h>
/* time, CLOCKS_PER_SEC */
#include <time.h>
/* Libs for Unix and Unix-like systems */
#ifdef __unix__
	/* for gettimeofday */
    #include <sys/time.h>
#endif

/**
 .. c:typedef:: Matrix

    Multidimensional matrix with any sizes by dimension.

    :c:member:: void *data

        A pointer to the data block of the matrix.

    :c:member:: size_t *sizes

        An array of size_t values representing the dimensions of the matrix.

    :c:member:: uint8_t num_dimensions

        The number of dimensions of the matrix.

    :c:member:: size_t size_of_type

        The size of an element.
*/
typedef struct {
    void * data;
    size_t * sizes;
    uint8_t num_dimensions;
    size_t size_of_type;
} Matrix;


/**
    .. c:function:: void * matrixAlloc(size_t *sizes, uint8_t numDimensions)

    Create and initialize a Matrix.

    :param sizes: An array representing the dimensions of the matrix.
    :type sizes: pointer to size_t

    :param numDimensions: The number of dimensions of the matrix.
    :type numDimensions: uint8_t

    :param size_of_type: The size of an element.
    :type size_of_type: size_t

    :return: A pointer to the allocated memory for the matrix.
    :rtype: pointer to double
*/
Matrix * matrix_init(size_t * sizes, uint8_t num_dimensions, size_t size_of_type);

void matrix_destruct(Matrix ** self);

size_t matrix_offset(Matrix * self, size_t * indices);

void matrix_get(Matrix * self, size_t * indices, void * write_location, size_t size_of_type);

void matrix_set(Matrix * self, size_t * indices, void * read_location, size_t size_of_type);

/* Normalize data in a vector */
void normalize(double * vec, uint64_t size);

/* Get the continuos value from a quantized binary sample */
double getQuantizationLevel(uint64_t binary, uint64_t nbits, double minValue, double maxValue);

/* Vector Random Permutation */
void permutation(int * vec, uint64_t size);

#endif /* _MMATH_H  */
