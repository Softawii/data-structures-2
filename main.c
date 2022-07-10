#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "include/client/cliente.h"
#include "include/core/intercalation.h"
#include "include/core/replacement_selection.h"
#include "include/utils/utils.h"
#include <dirent.h>

void show_file(char * file_name, from_stream from) {
    FILE * file = fopen(file_name, "rb");
    if(file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    while(ftell(file) < size) {
        var temp = from(file);

        if(temp != NULL) cliente_show(temp);
        else printf("Error: empty file\n");
    }
    fclose(file);
}

void file_manager() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(starts_with("partition_", dir->d_name)) {
                printf("Showing Content in '%s'\n", dir->d_name);
                show_file(dir->d_name, cliente_from_stream);
            }
        }
        closedir(d);
    }
}


int main(int argc, char **argv) {

    // Argc = exe, source, dest
    if(argc < 3) {
        printf("ERROR: You need pass two arguments, like: %s <source> <dest>\n", argv[0]);
        exit(1);
    }

    char * source_file = argv[1];
    char * output_file = argv[2];

    int max_files            = 4;
    int registries_in_memory = 5;

    for(int i = 3; i < argc; i++) {
        if(strcmp(argv[i], "--max-files") == 0 && (i + 1) < argc) {
            max_files = atoi(argv[i + 1]);
            i++;
        } else if(strcmp(argv[i], "--registries-in-memory") == 0 && (i + 1) < argc) {
            registries_in_memory = atoi(argv[i + 1]);
            i++;
        } else {
            printf("ERROR: Unknown argument '%s'\n", argv[i]);
            exit(1);
        }
    }

    printf("Max Files: %d\n", max_files);
    printf("Registries in Memory: %d\n", registries_in_memory);
    printf("\n\n");

    printf("Generating Partitions!\n");
    generate_partitions(registries_in_memory, source_file, cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream, (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Showing Source File!\n");
    show_file(source_file, cliente_from_stream);

    file_manager();

    intercalation(max_files, "partition_", output_file, cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream,
                  (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Showing Output File!\n");
    show_file(output_file, cliente_from_stream);

    return 0;
}
