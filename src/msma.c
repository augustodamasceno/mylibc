/* Mylibc Simple Moving Average
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* srand, rand, malloc, free */
#include <stdlib.h>
/* nan */
#include <math.h>

#include "msma.h"

SimpleMovingAverage sma_init(unsigned long period){
    SimpleMovingAverage sma;
    sma.period = period;
    sma.ready = TRUE;
    sma.sma = 0;
    sma.sum = 0;
}
