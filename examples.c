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
	setColor(GREEN_BRIGHT);
	setColor(BLACK_BACKGROUND);
	printf("Usage examples for personalc library.\n\n");

	printf(">> Example for function ");
	printf("double ** matrixAlloc(int r, int c)\n");
	setColor(GREEN);
	printf("r = 2 and c = 3\n\n");
	setColor(YELLOW);
	double ** matrix = matrixAlloc(2,3);
	srand (time(NULL));	/* Initialize random seed */
	int i,j;
	for (i=0; i<2; i++)
	{
		for (j=0; j<3; j++)
		{
			matrix[i][j] = ( (float) (rand() % 10000) ) / 100.0;
			printf("%05.2f  ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	setColor(GREEN_BRIGHT);
	printf(">> Free the memory allocated for the matrix.\n");
	setColor(GREEN);
	printf("matrixFree(matrix,2,3)\n\n");	
	matrixFree(matrix,2,3);

	setColor(GREEN_BRIGHT);
	printf(">> Example for function ");
	printf("void functionParameter(float(*fun)(float,float)\n");
	printf("fun = float myfunction(float a, float b) { return a + b; }\n");
	setColor(YELLOW);
	functionParameter(myfunction);
	printf("\n");

	setColor(GREEN_BRIGHT);
	printf(">> Example for functions ");
	printf("getTime and getTimeInterval.\n");
	setColor(GREEN);
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
	setColor(YELLOW);
	printf("Elapsed time: %.6fs\n\n",getTimeInterval(begin,_end));
	
	setColor(GREEN_BRIGHT);
	printf(">> Examples for function ");
	printf("void setColor(int value)\n");
	printf("value = Color Macros\n");
	setColor(GREEN);
	printf("Set font color, example: setColor(RED) \n");
	printf("Set font style, example: setColor(STYLE_UNDERLINE)\n");
	printf("Set background color, example: setColor(WHITE_BRIGHT_BACKGROUND)\n");
	printf("After print, reset the color modification: ");
	printf("setColor(COLOR_RESET)\n\n");
	setColor(RED);
	printf("RED\n");
	setColor(COLOR_RESET);
	setColor(BLUE_BRIGHT);
	printf("BLUE_BRIGHT\n");
	setColor(COLOR_RESET);
	setColor(YELLOW_BACKGROUND);
	printf("YELLOW_BACKGROUND\n");
	setColor(COLOR_RESET);
	setColor(RED);
	setColor(MAGENTA_BRIGHT_BACKGROUND);
	printf("RED + MAGENTA_BRIGHT_BACKGROUND\n");
	setColor(COLOR_RESET);
	setColor(BLUE_BRIGHT);
	setColor(STYLE_BOLD);
	printf("BLUE_BRIGHT + SYLE_BOLD\n");
	setColor(COLOR_RESET);
	setColor(CYAN_BRIGHT);
	setColor(STYLE_UNDERLINE);
	printf("CYAN_BRIGHT + STYLE_UNDERLINE\n");
	setColor(COLOR_RESET);
	setColor(GREEN);
	setColor(STYLE_REVERSED);
	printf("CYAN_BRIGHT + STYLE_REVERSED\n\n");
	
	setColor(COLOR_RESET);
	setColor(BLACK_BACKGROUND);
	setColor(GREEN_BRIGHT);

	printf(">> Example for function ");
	printf("void normalize(double * vec, int size)\n");
	setColor(GREEN);
	printf("vect = random data, size = 10\n\n");
	setColor(YELLOW);
	double * vec = (double*) malloc(sizeof(double)*10);
	/* Random seed already initialized */
	printf("Original:\n");
	for (i=0; i<10; i++)
	{
		vec[i] = ( (float) (rand() % 10000) ) / 100.0;
		printf("%07.4f  ",vec[i]);
	}
	printf("\n");
	printf("Normalized:\n");
	normalize(vec,10);
	for (i=0; i<10; i++)
		printf("%07.4f  ",vec[i]);
	printf("\n\n");
	free(vec);

	setColor(GREEN_BRIGHT);
	printf(">> Example for function double ");
	printf("getQuantizationLevel(uint64_t binary, ");
	printf("double minValue, double maxValue)\n");
	setColor(GREEN);
	printf("binary = 0b000 to 0b111, nbits = 3, minValue = -5, maxValue = 5\n\n");
	setColor(YELLOW);
	uint64_t binary = 0;
	for (i=0; i<8; i++)
	{
		printf("Binary ");
		printBin(binary+i);
		printf("\nQuantization Level: %06.4f\n",getQuantizationLevel(binary+i,3,-5,5));
	}
	printf("\n\n");

	setColor(COLOR_RESET);
	return 0;
} 

