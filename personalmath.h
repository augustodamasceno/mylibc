/* Personal reference to C programming
 *
 * Copyright (c) 2018, Augusto Damasceno.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PERSONALMATH_H
#define _PERSONALMATH_H

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

#endif /* _PERSONALMATH_H  */
