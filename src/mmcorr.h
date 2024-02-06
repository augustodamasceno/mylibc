/* Mylibc Moving Correlation
 *
 * Copyright (c) 2018-2024, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MMCORR_H
#define _MMCORR_H

/* Integer Types */
#include <stdint.h>
#include "msqueue.h"

typedef struct {
    StaticQueue * queue;
	uint64_t period;
} MovingCorrelation;

MovingCorrelation * mcorr_init(uint64_t period);
void mcorr_destruct(MovingCorrelation ** self);
void mcorr_add(MovingCorrelation * self, double * value);
double mcorr_get(MovingCorrelation * self, StaticQueue * second_variable);

#endif /* _MMCORR_H  */
