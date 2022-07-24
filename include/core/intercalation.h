//
// Created by yancf on 02/07/2022.
//

#ifndef REPLACEMENTSELECTION_INTERCALATION_H
#define REPLACEMENTSELECTION_INTERCALATION_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "core.h"
#include "../../libs/queue/queue.h"
#include "../utils/utils.h"
#include "../../libs/priority_queue/pqueue.h"

typedef struct {
    FILE       * file;
    var          next;
    comparator * comp;
    char       * name;
} FileStream;


int file_stream_comparator (var a, var b);

Queue* set_queue(char * prefix);

void intercalation_iteration(char * output_file, PQueue * file_streams, from_stream from, to_stream to, show show);

void intercalation_open_files(PQueue * file_streams, Queue * partitions_queue, int64_t max_files, from_stream from, comparator comp, show show);

void intercalation(int64_t max_files, char * file_prefix, char * final_output, from_stream from, to_stream to, comparator comp, show show);

#endif //REPLACEMENTSELECTION_INTERCALATION_H
