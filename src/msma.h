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
#include "mqueue.h"


typedef struct {
    double sma;
    double sum;
    Queue * values;
    unsigned char ready;
    uint64_t period;

} SimpleMovingAverage;

SimpleMovingAverage * sma_init(uint64_t period);
void sma_destruct(SimpleMovingAverage ** self);
void sma_add(SimpleMovingAverage * self, double * value);
double sma_get(SimpleMovingAverage * self);

#endif /* _MSMA_H  */
