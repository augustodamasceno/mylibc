/* Mylibc Utils
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */


#include "mutils.h"


/* Receive a function as parameter */
void functionParameter(float(*fun)(float,float))
{
	printf("functionParameter: %.4f\n",fun(2.0,3.0));
}

/* Get time to measure performance */
#ifdef __unix__
	struct timeval getTime(void)
	{	
		struct timeval t;
		gettimeofday(&t, NULL);
		return t;
	} 

	double getTimeInterval(struct timeval begin, struct timeval _end)
	{
		return ((_end.tv_sec+_end.tv_usec/1000000.0)) - \
            (begin.tv_sec+begin.tv_usec/1000000.0);
	}
#else
	clock_t getTime(void)
	{
		clock_t t = clock();
		return t;
	}

	double getTimeInterval(clock_t begin, clock_t _end)
	{
		return  ((float)(begin-_end))/CLOCKS_PER_SEC;
	}
#endif

