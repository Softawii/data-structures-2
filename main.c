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

void generate_clientes(char * output_file, int64_t size) {

    FILE * target = fopen(output_file, "wb");

    char names[][50] = {
            {"Victor"},
            {"Eduardo"},
            {"Romulo"},
            {"Mateus"},
            {"Yan"},
            {"Nicolas"},
            {"Sergio"},
            {"Isaque"},
            {"Gabriel"},
            {"Mari"},
            {"Zoe"},
            {"Raika"},
            {"Nina"},
            {"Vicky"},
            {"Diana"},
            {"Giovanna"},
            {"Greta"},
            {"Maya"},
            {"Emma"},
            {"Gabriela"},
            {"Ravi"},
            {"Otto"},
            {"Noa"},
            {"Davi"},
            {"Lucca"},
            {"Zyan"},
            {"Bento"},
            {"Benjamin"},
            {"Theo"},
            {"Gael"},
            {"Miguel"},
            {"Arthur"},
            {"Gae"},
            {"Heitor"},
            {"Davi"},
            {"Gabriel"},
            {"Bernardo"},
            {"Samuel"},
            {"João Miguel"}
    };

    // Specifying a seed
    srand(100);
    for(int64_t i = 0; i < size; i++) {
        cliente clt;

        clt.id   = rand() % 10000000; // Random from 1 to size * 5
        strcpy(clt.nome, names[clt.id % 38]); // Random from 0 to 6
        strcpy(clt.nascimento, "10/12/2022");
        cliente_to_stream(target, &clt);
    }
    fclose(target);
}

int main() {

    printf("Generating Clients!\n");
    generate_clientes("clientes.dat", 50);

    printf("Generating Partitions!\n");
    generate_partitions(5, "clientes.dat", cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream,
                        (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Showing Source File!\n");
    show_file("clientes.dat", cliente_from_stream);

    file_manager();

    intercalation(4, "partition_", cliente_from_stream, (void (*)(FILE *, var)) cliente_to_stream,
                  (int (*)(var, var)) id_comparator, (void (*)(var)) cliente_show);

    printf("Hello, World!\n");
    return 0;
}
