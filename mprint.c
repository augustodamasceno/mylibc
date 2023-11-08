/* Mylibc Print
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "mprint.h"


/* Set Color and Style with ANSI SCAPES */
void setColor(int value)
{
	printf("\033[%dm",value);
}

/* Print in binary format */
void printBin(uint64_t value)
{
	int i;
	uint64_t getBit = 1;
	getBit = getBit<<63;
	printf("0b");
	for (i=63; i>=0; i--)
	{
		if(getBit & value)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		getBit = getBit>>1;
	}
}
