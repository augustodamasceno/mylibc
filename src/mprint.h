/* Mylibc Print
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MPRINT_H
#define _MPRINT_H

/* for printf, scanf, puts, NULL */
#include <stdio.h>
#include <inttypes.h>

/* Color */
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define BLACK_BRIGHT 90
#define RED_BRIGHT 91
#define GREEN_BRIGHT 92
#define YELLOW_BRIGHT 93
#define BLUE_BRIGHT 94
#define MAGENTA_BRIGHT 95
#define CYAN_BRIGHT 96
#define WHITE_BRIGHT 97
#define BLACK_BACKGROUND 40
#define RED_BACKGROUND 41
#define GREEN_BACKGROUND 42
#define YELLOW_BACKGROUND 43
#define BLUE_BACKGROUND 44
#define MAGENTA_BACKGROUND 45
#define CYAN_BACKGROUND 46
#define WHITE_BACKGROUND 47
#define BLACK_BRIGHT_BACKGROUND 100
#define RED_BRIGHT_BACKGROUND 101
#define GREEN_BRIGHT_BACKGROUND 102
#define YELLOW_BRIGHT_BACKGROUND 103
#define BLUE_BRIGHT_BACKGROUND 104
#define MAGENTA_BRIGHT_BACKGROUND 105
#define CYAN_BRIGHT_BACKGROUND 106
#define WHITE_BRIGHT_BACKGROUND 107
#define STYLE_BOLD 1
#define STYLE_UNDERLINE 4
#define STYLE_REVERSED 7
#define COLOR_RESET 0

/* Set Color and Style with ANSI SCAPES */
void setColor(int value);

/* Print in binary format */
void printBin(uint64_t value);
	
/* Format Specifiers for Generic Data Print */
int format_specifiers_unsigned(const char * format);
int format_specifiers_int(const char * format);
int format_specifiers_long(const char * format);
int format_specifiers_double(const char * format);

#endif /* _MPRINT_H  */
