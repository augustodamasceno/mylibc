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

#ifndef _PERSONAL_H
#define _PERSONAL_H

/* Libs */

/* for printf, scanf, puts, NULL */
#include <stdio.h>
#include <inttypes.h>

/* Macros */

/* Color Macros*/
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

/* Functions */

/* Set Color and Style with ANSI SCAPES */
void setColor(int value);

/* Print in binary format */
void printBin(uint64_t value);
	
#endif /* _PERSONAL_H  */
