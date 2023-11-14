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


void run_suite(Suite * suite, char * suite_name);

int main()
{
	Suite * s_math = suite_mmath();
	Suite * s_list = suite_mlist();
    Suite * s_queue = suite_mqueue();

	run_suite(s_math, "mmath");
	run_suite(s_list, "mlist");
    run_suite(s_queue, "mqueue");

	return 0;
} 

void run_suite(Suite * suite, char * suite_name){
    SRunner *runner = srunner_create(suite);
    srunner_set_fork_status (runner, CK_NOFORK);
    srunner_run_all(runner, CK_VERBOSE);
    int num_tests = srunner_ntests_run(runner);
    int num_failures = srunner_ntests_failed(runner);
    int num_success = num_tests - num_failures;
    srunner_free(runner);
    printf("Suite for %s: Sucess: %d Failures: %d\n", suite_name, num_success, num_failures);
}
