/* Mylibc Math
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MYMATH_H
#define _MYMATH_H

/* Libs */

/* for srand, rand, malloc, free */
#include <stdlib.h>
/* for pow */
#include <math.h>
/* for time, CLOCKS_PER_SEC */
#include <time.h>
/* Libs for Unix and Unix-like systems */
#ifdef __unix__
	/* for gettimeofday */
    #include <sys/time.h>
#endif
/* for uintX_t types  */
#include <inttypes.h>

/* Matrix Memory Allocation */
double ** matrixAlloc(int r, int c);

/* Matrix Free Memory Allocated */
void matrixFree(double ** matrix, int r, int c);

/* Normalize data in a vector */
void normalize(double * vec, int size);

/* Get the continuos value from a quantized binary sample */
double getQuantizationLevel(uint64_t binary, int nbits, double minValue, double maxValue);

/* Vector Random Permutation */
void permutation(int * vec, int size);

#endif /* _MYMATH_H  */
