/* Mylibc Simple Moving Average
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MSMA_H
#define _MSMA_H

/* Integer Types */
#include <stdint.h>
#include "msqueue.h"


typedef struct {
    StaticQueue * values;
    uint64_t period;
	uint64_t nan_counter;
	uint8_t ignore_nan;
	uint8_t nan_to_zero;
} SimpleMovingAverage;

SimpleMovingAverage * sma_init(uint64_t period);
void sma_destruct(SimpleMovingAverage ** self);
void sma_add(SimpleMovingAverage * self, double * value);
double sma_get(SimpleMovingAverage * self);

#endif /* _MSMA_H  */

