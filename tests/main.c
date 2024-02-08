/* Mylibc Tests
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
/* sprintf, fprintf, stderr */
#include <stdio.h>
#include <check.h>

#include "test_mmath.h"
#include "test_mlist.h"
#include "test_mqueue.h"
#include "test_msma.h"
#include "test_mmcorr.h"
#include "test_mlistcont.h"
#include "test_msqueue.h"
#include "test_mcsv.h"
#include "test_mstring.h"


void run_suite(Suite * suite, const char * suite_name);

int main()
{
	Suite * s_math = suite_mmath();
	Suite * s_list = suite_mlist();
    Suite * s_queue = suite_mqueue();
	Suite * s_squeue = suite_msqueue();
	Suite * s_sma = suite_msma();
    Suite * s_mcorr = suite_mmcorr();
	Suite * s_list_cont = suite_mlist_cont();
	Suite * s_string = suite_mstring();
	Suite * s_csv = suite_mcsv();
    
	printf("\n");
	run_suite(s_math, "mmath");
    printf("\n");
	run_suite(s_list, "mlist");
    printf("\n");
    run_suite(s_queue, "mqueue");
    printf("\n");
	run_suite(s_squeue, "msqueue");
    printf("\n");
    run_suite(s_sma, "msma");
    printf("\n");
    run_suite(s_mcorr, "mcorr");
	printf("\n");
	run_suite(s_list_cont, "mlist_cont");
	printf("\n");
	run_suite(s_string, "mstring");
	printf("\n");
	run_suite(s_csv, "mcsv");
	return 0;
} 

void run_suite(Suite * suite, const char * suite_name){
    SRunner *runner = srunner_create(suite);
    srunner_set_fork_status (runner, CK_NOFORK);
    srunner_run_all(runner, CK_VERBOSE);
    int num_tests = srunner_ntests_run(runner);
    int num_failures = srunner_ntests_failed(runner);
    int num_success = num_tests - num_failures;
    srunner_free(runner);
    printf("Suite for %s\n\tSucess: %d\n\tFailures: %d\n"
           , suite_name
           , num_success
           , num_failures);
}

