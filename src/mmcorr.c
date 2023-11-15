/* Mylibc Moving Correlation
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* srand, rand, malloc, free */
#include <stdlib.h>
/* nan, sqrt */
#include <math.h>
#include "mmcorr.h"


MovingCorrelation * mcorr_init(uint64_t period){
    MovingCorrelation * mcorr = malloc(sizeof(MovingCorrelation));
    mcorr->period = period;
    mcorr->values = list_init(sizeof(double));
    return mcorr;
}

void mcorr_destruct(MovingCorrelation ** self){
    list_destruct(&((*self)->values));
    free(*self);
    *self = NULL;
}

void mcorr_add(MovingCorrelation * self, double * value){
    if (isnan(*value) == 0){
        if (self->values->size == self->period)
            list_remove_front(self->values);
        list_insert_back(self->values, (void*)value);
    }
}

double mcorr_get(MovingCorrelation * self, List * second_variable){
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
    uint64_t index = 0;
    if (!(   (self->values->size < self->period)
          || (second_variable->size < self->period) )){
       
        for (index=0; index<self->period; index++){
            list_get(self->values, (void*)&first, index);
            list_get(second_variable, (void*)&second, index);
            sum_first += first;
            sum_second += second;
            sum_mult += first * second;
            sum_sq_first += first * first;
            sum_sq_second += second * second;
        }
        
        numerator = ((double) self->period) * sum_mult - sum_first * sum_second;
        denominator_a = ((double) self->period) * sum_sq_first - sum_first * sum_first;
        denominator_b = ((double) self->period) * sum_sq_second  - sum_second * sum_second;
        denominator = sqrt(denominator_a * denominator_b);
        correlation = numerator / denominator;
    }
    return correlation;
}
