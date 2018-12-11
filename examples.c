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

#define MILION 1000000


float myfunction(float a, float b)
{
	return a + b;
}


int main(int argc, char ** argv)
{
	printf("Usage examples for personalc library.\n\n");

	printf(">> Example for function ");
	printf("double ** matrixAlloc(int r, int c)\n");
	printf("r = 2 and c = 3\n\n");
	double ** matrix = matrixAlloc(2,3);
	srand (time(NULL));	/* Initialize random seed */
	int i,j;
	for (i=0; i<2; i++)
	{
		for (j=0; j<3; j++)
		{
			matrix[i][j] = ( (float) (rand() % 10000) ) / 100.0;
			printf("%.2f  ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	/* Free memory for matrix allocated */
	printf("Free the memory allocated for the matrix.\n");
	printf("matrixFree(matrix,2,3)\n\n");
	matrixFree(matrix,2,3);

	printf(">> Example for function ");
	printf("void functionParameter(float(*fun)(float,float)\n");
	printf("The function fun returns the sum of arguments\n");
	functionParameter(myfunction);
	printf("\n");	

	printf(">> Example for functions ");
	printf("getTime and getTimeInterval.\n");
	printf("Calculates sum 100 milion times.\n\n");
#ifdef __unix__
	struct timeval begin = getTime();	
#else
	clock_t begin = getTime();
#endif	
	for(i=0; i<(100*MILION); i++)
		j++;
#ifdef __unix__
	struct timeval _end = getTime();	
#else
	clock_t _end = getTime();
#endif	
	printf("Elapsed time: %.6f.\n\n",getTimeInterval(begin,_end));

	return 0;
} 

