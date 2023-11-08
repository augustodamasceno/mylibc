/* Mylibc Utils
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MUTILS_H
#define _MUTILS_H

/* for printf, scanf, puts */
#include <stdio.h>
/* for NULL */
#include <stdlib.h>
/* for time, CLOCKS_PER_SEC */
#include <time.h>
/* Libs for Unix and Unix-like systems */
#ifdef __unix__
	/* for gettimeofday */
    #include <sys/time.h>
#endif


/* Receive a function as parameter */
void functionParameter(float(*fun)(float,float)); 

/* Get time to measure performance */
#ifdef __unix__
	struct timeval getTime(void);
	double getTimeInterval(struct timeval begin, struct timeval _end);
#else
	clock_t getTime(void);
	double getTimeInterval(clock_t begin, clock_t _end);
#endif

#endif /* _MUTILS_H  */

