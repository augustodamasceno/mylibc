/* Mylibc String Tests
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "test_mstring.h"
#include "../src/mstring.h"


START_TEST (testStringSize) {
	uint64_t expected = 0;
	const char A[] = "";
	const char B[] = "H";
	const char C[] = "Hi!";
	char D[10];
	D[0] = '\0';
	
	expected = 0;
	ck_assert_int_eq(expected, string_size(A)); 
	expected = 1;
	ck_assert_int_eq(expected, string_size(B)); 
	expected = 3;
	ck_assert_int_eq(expected, string_size(C)); 
	expected = 0;
	ck_assert_int_eq(expected, string_size(D));
	sprintf(D, "12345");
	expected = 5;
	ck_assert_int_eq(expected, string_size(D));
	D[3] = '\0';
	expected = 3;
	ck_assert_int_eq(expected, string_size(D));
}


START_TEST (testStringCountChar) {
	uint64_t expected = 0;
	const char STR[] = "You shall not pass!";
	expected = 1;
	ck_assert_int_eq(expected, string_count_char(STR, '!'));
	expected = 1;
	ck_assert_int_eq(expected, string_count_char(STR, 'Y'));
	expected = 2;
	ck_assert_int_eq(expected, string_count_char(STR, 'o'));
	expected = 3;
	ck_assert_int_eq(expected, string_count_char(STR, ' '));
}

START_TEST (testStringIn) {
	uint64_t expected = 0;
	const char STR[] = "Identity theft is not a joke, Jim!";
	uint8_t contain = 0;

	contain = char_in(STR, 'T');
	expected = 0;
	ck_assert_int_eq(expected, contain);
	contain = char_in(STR, '!');
	expected = 1;
	ck_assert_int_eq(expected, contain);
	contain = char_in(STR, 'I');
	expected = 1;
	ck_assert_int_eq(expected, contain);
	contain = char_in(STR, 'a');
	expected = 1;
	ck_assert_int_eq(expected, contain);
	contain = char_in(STR, '\n');
	expected = 0;
	ck_assert_int_eq(expected, contain);
}


START_TEST (testStringContains) {
	uint8_t expected = 0;
	uint8_t contains = 0;
	const char STR[] = "I'm sorry, what was the question? ";
	
	expected = 1;
	contains = string_contains(STR, " \n-,");
	ck_assert_int_eq(expected, contains);

	expected = 0;
	contains = string_contains(STR, "!");
	ck_assert_int_eq(expected, contains);
}

START_TEST (testStringRemove) {
	const char STR[] = "  Parkour\n\tParkour;";
	char * stripped = string_remove(STR, " \n\t;");
	ck_assert_str_eq(stripped, "ParkourParkour");
	free(stripped);
}

START_TEST (testStringCut) {
	/* Size 19. Indexes 0 to 18. */
	const char STR[] = "You shall not pass!";
	char * cut = string_cut(STR, 0, 1000);
	ck_assert_str_eq(cut, "You shall not pass!");
	free(cut);
	cut = string_cut(STR, 0, 18);
	ck_assert_str_eq(cut, "You shall not pass!");
	free(cut);
	cut = string_cut(STR, -1, 5);
	ck_assert_ptr_null(cut);
	cut = string_cut(STR, 0, 2);
	ck_assert_str_eq(cut, "You");
	free(cut);
	cut = string_cut(STR, 14, 18);
	ck_assert_str_eq(cut, "pass!");
	free(cut);
}

START_TEST (testStringCount) {
	uint64_t expected = 0;
	/* Size 19. Indexes 0 to 18. */
	const char STR[] = "Fact. Bears eat beets. Bears. Beets. Battlestar Galactica.";
	expected = 0;
	ck_assert_int_eq(expected, string_count(STR, "BeaR"));
	expected = 2;
	ck_assert_int_eq(expected, string_count(STR, "Bears"));
	expected = 1;
	ck_assert_int_eq(expected, string_count(STR, "eat"));
	expected = 1;
	ck_assert_int_eq(expected, string_count(STR, "Fact"));
	expected = 1;
	ck_assert_int_eq(expected, string_count(STR, "Galactica."));
}


START_TEST (testStringSplit) {
	uint64_t expected = 0;
	const char STR[] = "That's what she said.";
	const char STR2[] = "I... declare... bankruptcy!";
	const char SEPARATOR[] = " ";
	char ** strings = NULL;
	uint64_t size;	
	uint64_t index = 0;

	strings = string_split(STR, SEPARATOR, &size);
	
	expected = 4;
	ck_assert_int_eq(expected, size);
	ck_assert_str_eq(strings[0], "That's");
	ck_assert_str_eq(strings[1], "what");
	ck_assert_str_eq(strings[2], "she");
	ck_assert_str_eq(strings[3], "said.");
	
	for (index=0; index<size; index++)
		free(strings[index]);
	free(strings);
	strings = NULL;

	strings = string_split(STR2, "I... declare... bankruptcy!", &size);
	expected = 2;
	ck_assert_str_eq(strings[0], "");
	ck_assert_str_eq(strings[1], "");

	for (index=0; index<size; index++)
		free(strings[index]);
	free(strings);
	strings = NULL;
}

Suite* suite_mstring(){
    Suite* suite = suite_create("String Suite");
    TCase* tc_string = tcase_create("String");

    tcase_add_test(tc_string, testStringSize);
	tcase_add_test(tc_string, testStringCountChar);
	tcase_add_test(tc_string, testStringIn);
	tcase_add_test(tc_string, testStringContains);
	tcase_add_test(tc_string, testStringCountChar);
	tcase_add_test(tc_string, testStringRemove);
	tcase_add_test(tc_string, testStringCut);
	tcase_add_test(tc_string, testStringCount);
	tcase_add_test(tc_string, testStringSplit);

	suite_add_tcase(suite, tc_string);
    return suite;
}

