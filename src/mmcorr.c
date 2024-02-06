/* Mylibc Moving Correlation
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* srand, rand, malloc, free */
#include <stdlib.h>
/* nan, sqrt */
#include <math.h>
#include <string.h>
#include "mmcorr.h"
#include "msqueue.h"


MovingCorrelation * mcorr_init(uint64_t period){
    MovingCorrelation * mcorr = malloc(sizeof(MovingCorrelation));
    mcorr->queue = squeue_init(sizeof(double), period);
	mcorr->period = period;
    return mcorr;
}

void mcorr_destruct(MovingCorrelation ** self){
    squeue_destruct(&((*self)->queue));
    free(*self);
    *self = NULL;
}

void mcorr_add(MovingCorrelation * self, double * value){
    if (isnan(*value) == 0)
        squeue_insert(self->queue, (void*)value);
}

double mcorr_get(MovingCorrelation * self, StaticQueue * second_variable){
    double correlation = NAN;
    double first = 0;
    double second = 0;
    double sum_first = 0;
    double sum_second = 0;
    double sum_mult = 0;
    double sum_sq_first = 0;
    double sum_sq_second = 0;
    double numerator = 0;
    double denominator_a = 0;
    double denominator_b = 0;
    double denominator = 0;
    uint64_t index_first = 0;
	uint64_t index_second = 0;
	uint64_t element_counter = self->period;
	char * memory_first = NULL;
	char * memory_second = NULL;
    if (   self->queue->size == self->period
		&& second_variable->size == self->period){
        index_first = self->queue->front;
		index_second = second_variable->front;
        while(element_counter > 0){
            memory_first = self->queue->values 
						   + self->queue->size_of_type 
						   * index_first;
			memory_second = second_variable->values 
						   + second_variable->size_of_type 
						   * index_second;
			memcpy(&first, memory_first, self->queue->size_of_type);
			memcpy(&second, memory_second, second_variable->size_of_type);
            sum_first += first;
            sum_second += second;
            sum_mult += first * second;
            sum_sq_first += first * first;
            sum_sq_second += second * second;
			element_counter--;
			index_first = (index_first + 1) % self->period;
			index_second = (index_second + 1) % self->period;
        }
        
        numerator = ((double) self->period) * sum_mult - sum_first * sum_second;
        denominator_a = ((double) self->period) * sum_sq_first - sum_first * sum_first;
        denominator_b = ((double) self->period) * sum_sq_second  - sum_second * sum_second;
        denominator = sqrt(denominator_a * denominator_b);
        correlation = numerator / denominator;
    }
    return correlation;
}

