/* Mylibc Simple Moving Average
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <math.h>

#include "msma.h"


SimpleMovingAverage * sma_init(uint64_t period){
    SimpleMovingAverage * sma = malloc(sizeof(SimpleMovingAverage));
	uint64_t max_size = period;
    sma->values = squeue_init(sizeof(double), max_size);
    sma->period = period;
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
	double write = NAN;
	if (self->ignore_nan == 0 || (self->ignore_nan != 0 && isnan(*value) == 0)){
		if (self->values->size == self->period){
			squeue_front(self->values, (void*)&write);
			if (isnan(write) != 0)
				self->nan_counter--;
			squeue_remove(self->values);
		}
		if (isnan(*value) != 0)
			self->nan_counter++;
		squeue_insert(self->values, (void*)value);
	}
}

double sma_get(SimpleMovingAverage * self){
    double value = NAN;
	double period = (double) self->period;
	if (self->ignore_nan == 0 && self->nan_to_zero != 0)
		period -= self->nan_counter;
    if (self->values->size == self->period){
		if (self->nan_to_zero != 0)
			value = squeue_sumnan_double(self->values) / period;	
		else	
			value = squeue_sum_double(self->values) / period;		
	}
	return value;
}

