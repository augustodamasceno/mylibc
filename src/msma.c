/* Mylibc Simple Moving Average
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* srand, rand, malloc, free */
#include <stdlib.h>
/* nan */
#include <math.h>

#include "msma.h"


SimpleMovingAverage * sma_init(uint64_t period){
    SimpleMovingAverage * sma = malloc(sizeof(SimpleMovingAverage));
	uint64_t max_size = period;
    sma->values = squeue_init(sizeof(double), max_size);
    sma->period = period;
    sma->sma = 0;
    sma->sum = 0;
    return sma;
}

void sma_destruct(SimpleMovingAverage ** self){
    squeue_destruct(&((*self)->values));
    free(*self);
    *self = NULL;
}

void sma_add(SimpleMovingAverage * self, double * value){
    double write = NAN;
    if (isnan(*value) == 0){
        if (self->values->size == self->period){
            squeue_front(self->values, (void*)&write);
            self->sum += -1 * write + (*value);
            squeue_remove(self->values);
        } else
            self->sum += *value;
        squeue_insert(self->values, (void*)value);
        self->sma = self->sum / (double) self->period;
    }
}

double sma_get(SimpleMovingAverage * self){
    double value = NAN;
    if (self->values->size == self->period)
        value = self->sma;
    return value;
}

