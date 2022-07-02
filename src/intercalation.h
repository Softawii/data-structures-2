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
#include "core.h"
#include "queue.h"
#include "utils.h"


Queue* set_queue(char * prefix) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    Queue * queue = newQueue(-1);

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(starts_with(prefix, dir->d_name)) {
                printf("Adding '%s' to queue\n", dir->d_name);
                char * file_name = malloc(sizeof(char) * (strlen(dir->d_name) + 1));
                strcpy(file_name, dir->d_name);
                enqueue(queue, file_name);
            }
        }
        closedir(d);
    }

    return queue;
}

void intercalation(int64_t max_files, char * file_prefix, from_stream from, to_stream to, comparator comp, show show) {
    Queue * queue = set_queue(file_prefix);


    freeQueue(queue);
}

#endif //REPLACEMENTSELECTION_INTERCALATION_H
