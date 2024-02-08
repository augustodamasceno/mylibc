/* Mylibc String
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MSTRING_H
#define _MSTRING_H

#include <stdint.h>

uint8_t char_in(const char * string, const char c);
uint8_t string_contains(const char * string, const char * chars);
char * string_remove(const char * string, const char * chars);
uint64_t string_size(const char * string);
uint64_t string_count_char(const char * string,
						   char c);
char * string_cut(const char * string, uint64_t start, uint64_t end);
uint64_t string_count(const char * string,
					  const char * substring);
char ** string_split(const char * string,
				  const char * separator,
				  uint64_t * size);

#endif /* _MSTRING_H  */

