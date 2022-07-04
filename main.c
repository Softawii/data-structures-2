#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "test/cliente.h"
#include "src/intercalation.h"
#include "src/replacement_selection.h"
#include "src/utils.h"
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

int main() {

    char source_file[255] = "../libs/mock/db.dat";
    char output_file[255] = "../libs/mock/sorted.dat";

    printf("Generating Partitions!\n");
    generate_partitions(5, source_file, cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream,
                        (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Showing Source File!\n");
    show_file(source_file, cliente_from_stream);

    file_manager();

    intercalation(4, "partition_", output_file, cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream,
                  (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Showing Output File!\n");
    show_file(output_file, cliente_from_stream);

    return 0;
}
