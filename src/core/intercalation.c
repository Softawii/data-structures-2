//
// Created by yancf on 05/07/2022.
//
#include "../../include/core/intercalation.h"


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

void intercalation_iteration(char * output_file, PQueue * file_streams, from_stream from, to_stream to, show show) {

    FILE * output_stream = fopen(output_file, "wb");

    printf("Writing %s\n", output_file);
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
            remove(fs->name);
            free(fs->name);
            free(fs);
        }
    }
    printf("End %s\n", output_file);

    fclose(output_stream);
}

void intercalation_open_files(PQueue * file_streams, Queue * partitions_queue, int64_t max_files, from_stream from, comparator comp, show show) {
    for (int i = 0; i < max_files - 1; i++) {
        char *file_name = dequeue(partitions_queue);

        // We don't have any file to read
        if (file_name == NULL) break;

        // Construct the file stream.
        FileStream *file_stream = malloc(sizeof(FileStream));

        file_stream->file = fopen(file_name, "rb");
        file_stream->name = file_name;
        file_stream->comp = comp;
        file_stream->next = from(file_stream->file);

        //show(file_stream->next);

        pqueue_enqueue(file_streams, file_stream);
    }
}

void intercalation(int64_t max_files, char * file_prefix, char * final_output, from_stream from, to_stream to, comparator comp, show show) {
    // FILE NAME: partition_1, partition_2, ..., partition_n
    Queue  * partitions_queue   = set_queue(file_prefix);
    PQueue * file_streams       = pqueue_new((int (*)(const void *, const void *)) file_stream_comparator, max_files - 1);
    int      iterator           = 1;
    char     output_file[255];

    while(queueSize(partitions_queue) > 0) {
        // It's in a loop, max files - 1 times, because we need to intercalate all files.
        intercalation_open_files(file_streams, partitions_queue, max_files, from, comp, show);

        // Creating the output name
        sprintf(output_file, "intercalation_%d.dat", iterator);
        iterator += 1;

        // One output file
        intercalation_iteration(output_file, file_streams, from, to, show);

        if (queueSize(partitions_queue) == 0) {
            remove(final_output);

            if(rename(output_file, final_output) != 0) {
                printf("Error renaming file, %s\n", strerror(errno));
            }
            break;
        } else {
            // Adding current file to queue
            char *_file = (char *) malloc(sizeof(output_file));
            strcpy(_file, output_file);
            enqueue(partitions_queue, _file);
        }
    }

    // Ending
    freeQueue(partitions_queue);
    pqueue_delete(file_streams);
}

