/* Mylibc Print
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include "mprint.h"


void setColor(int value)
{
	printf("\033[%dm",value);
}

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

int format_specifiers_unsigned(const char * format){
	int confirmed = 0;
	if ((strchr(format, 'u') != NULL) 
			|| (strchr(format, 'o') != NULL) 
			|| (strchr(format, 'x') != NULL)
			|| (strchr(format, 'X') != NULL)) 
		confirmed = 1;
	return confirmed;
}

int format_specifiers_int(const char * format){
	int confirmed = 0;
	if ((strchr(format, 'd') != NULL) 
			|| (strchr(format, 'i') != NULL) 
			|| (strchr(format, 'h') != NULL)
			|| (strchr(format, 'j') != NULL)
			|| (strchr(format, 'z') != NULL)
			|| (strchr(format, 't') != NULL))
		confirmed = 1;
	return confirmed;
}

int format_specifiers_long(const char * format){
	int confirmed = 0;
	if ((strchr(format, 'l') != NULL))
		confirmed = 1;
	return confirmed;
}

int format_specifiers_double(const char * format){
	int confirmed = 0;
	if ((strchr(format, 'f') != NULL) 
			|| (strchr(format, 'F') != NULL) 
			|| (strchr(format, 'e') != NULL)
			|| (strchr(format, 'E') != NULL)
			|| (strchr(format, 'g') != NULL)
			|| (strchr(format, 'G') != NULL)
			|| (strchr(format, 'a') != NULL)
			|| (strchr(format, 'A') != NULL))
		confirmed = 1;
	return confirmed;
}

