/* Mylibc Simple Moving Average
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MSMA_H
#define _MSMA_H

/* Integer Types */
#include <stdint.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    double sma;
    double sum;
    unsigned char ready;
    unsigned long period;

} SimpleMovingAverage;

SimpleMovingAverage sma_init(unsigned long period);

//SimpleMovingAverage sma_add(SimpleMovingAverage * self, double value);

#endif /* _MSMA_H  */
