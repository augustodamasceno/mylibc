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
	sma->sum = 0;
	sma->ignore_nan = 0;
	sma->nan_to_zero = 0;
	sma->nan_counter = 0;
    return sma;
}

void sma_destruct(SimpleMovingAverage ** self){
    squeue_destruct(&((*self)->values));
    free(*self);
    *self = NULL;
}

void sma_add(SimpleMovingAverage * self, double * value){
	double value_adjusted = *value;
	double write = NAN;
	if (self->ignore_nan == 0 || (self->ignore_nan != 0 && isnan(*value) == 0)){
		if (self->nan_to_zero != 0 && isnan(*value) != 0){
			value_adjusted = 0;
			self->nan_counter++;
		}
		if (self->values->size == self->period){
			squeue_front(self->values, (void*)&write);
			if (isnan(write) != 0)
				self->nan_counter--;
			squeue_remove(self->values);
			self->sum -= value_adjusted;	
		}
		self->sum += value_adjusted;
		squeue_insert(self->values, (void*)&value_adjusted);
	}
}

double sma_get(SimpleMovingAverage * self){
    double value = NAN;
	double period = (double) self->period;
	if (self->nan_to_zero != 0)
		period -= self->nan_counter;
    if (self->values->size == self->period)
		value = squeue_sum_double(self->values) / period;		
    return value;
}

