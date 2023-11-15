/* Mylibc Moving Correlation
 *
 * Copyright (c) 2018-2023, Augusto Damasceno.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _MMCORR_H
#define _MMCORR_H

/* Integer Types */
#include <stdint.h>
#include "mlist.h"

typedef struct {
    List * values;
    uint64_t period;

} MovingCorrelation;

MovingCorrelation * mcorr_init(uint64_t period);
void mcorr_destruct(MovingCorrelation ** self);
void mcorr_add(MovingCorrelation * self, double * value);
double mcorr_get(MovingCorrelation * self, List * second_variable);

#endif /* _MMCORR_H  */
