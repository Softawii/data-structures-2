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
#include "../libs/queue/queue.h"
#include "utils.h"
#include "../libs/priority_queue/pqueue.h"

typedef struct {
    FILE       * file;
    var          next;
    comparator * comp;
    char       * name;
} FileStream;


int file_stream_comparator (var a, var b) {
    FileStream * fs_a = (FileStream *) a;
    FileStream * fs_b = (FileStream *) b;
    return (*fs_a->comp)(fs_a->next, fs_b->next) * -1;
}

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
    // FILE NAME: partition_1, partition_2, ..., partition_n
    Queue  * partitions_queue   = set_queue(file_prefix);
    PQueue * file_streams       = pqueue_new((int (*)(const void *, const void *)) file_stream_comparator, max_files - 1);
    int      iterator           = 1;
    char     output_file[255];

    // Iteration
    printf("KKKKKKKKKKKKKK\n");
    // It's in a loop, max files - 1 times, because we need to intercalate all files.
    for(int i = 0; i < max_files - 1; i++) {
        char *file_name = dequeue(partitions_queue);

        // We don't have any file to read
        if(file_name == NULL) break;

        // Construct the file stream.
        FileStream *file_stream = malloc(sizeof(FileStream));

        file_stream->file = fopen(file_name, "rb");
        file_stream->name = file_name;
        file_stream->comp = comp;
        file_stream->next = from(file_stream->file);

        show(file_stream->next);

        pqueue_enqueue(file_streams, file_stream);
    }

    // Creating the output file
    sprintf(output_file, "intercalation_%d.dat", iterator);
    iterator += 1;
    FILE * output_stream = fopen(output_file, "wb");

    printf("-------------------\n");
    // Loop Reading
    while(1 < 2) {
        FileStream * fs = pqueue_dequeue(file_streams);

        // End of Queue
        if(fs == NULL) {
            break;
        }

        // Writing next registry and replacing it (we need to free it ;))
        to(output_stream, fs->next);

        show(fs->next);

        free(fs->next);
        fs->next = from(fs->file);

        if(fs->next != NULL) {
            pqueue_enqueue(file_streams, fs);
        } else {
            fclose(fs->file);
            // remove(fs->name);
            free(fs->name);
            free(fs);
        }
    }
    fclose(output_stream);


    // Ending
    freeQueue(partitions_queue);
    pqueue_delete(file_streams);
}

#endif //REPLACEMENTSELECTION_INTERCALATION_H
