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


#include "personal.h"


/* Matrix Memory Allocation */
double ** matrixAlloc(int r, int c)
{
	double ** m = (double**) malloc(sizeof(double*)*r);
	int i;
	for(i=0; i<r; i++)
		m[i] = (double*) malloc(sizeof(double)*c);
	
	return m;
}

/* Matrix Free Memory Allocated */
void matrixFree(double ** matrix, int r, int c)
{
	int i;
	for (i=0; i<r; i++)
		free(matrix[i]);
	free(matrix);
}

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
