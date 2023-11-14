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

SimpleMovingAverage * sma_init(unsigned long period){
    SimpleMovingAverage * sma = malloc(sizeof(SimpleMovingAverage));
    sma->values = queue_init(sizeof(double));
    sma->period = period;
    sma->sma = 0;
    sma->sum = 0;
    return sma;
}

void sma_destruct(SimpleMovingAverage ** self){
    queue_destruct(&((*self)->values));
    free(*self);
    *self = NULL;
}

void sma_add(SimpleMovingAverage * self, double * value){
    double write = NAN;
    if (isnan(*value) == 0){
        if (queue_size(self->values) == self->period){
            queue_front(self->values, (void*)&write);
            self->sum += -1 * write + (*value);
            queue_remove(self->values);
        } else
            self->sum += *value;
        queue_insert(self->values, (void*)value);
        self->sma = self->sum / (double) self->period;
    }
}

double sma_get(SimpleMovingAverage * self){
    double value = NAN;
    if (queue_size(self->values) == self->period)
        value = self->sma;
    return value;
}
