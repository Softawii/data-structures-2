//
// Created by yancf on 26/06/2022.
//

#ifndef REPLACEMENTSELECTION_REPLACEMENT_SELECTION_H
#define REPLACEMENTSELECTION_REPLACEMENT_SELECTION_H

#include "core.h"

// #define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum STATE {
    FREEZE   = 0,
    ENABLED  = 1,
    NULLABLE = 2
} STATE;


typedef struct {
    var    value;
    STATE status;
} var_status;


bool all_freeze(var_status * elements, int64_t length);

void unfreeze(var_status * elements, int64_t length);

bool all_nullable(var_status * elements, int64_t length);

var_status * min(var_status * elements, int64_t length, comparator comp);

void generate_partitions(int64_t number_of_registries, char * input_file,  from_stream from, to_stream to, comparator comp, show show);

#endif //REPLACEMENTSELECTION_REPLACEMENT_SELECTION_H
