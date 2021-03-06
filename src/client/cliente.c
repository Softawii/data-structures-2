//
// Created by yancf on 05/07/2022.
//
#include "../../include/client/cliente.h"

var  cliente_from_stream(FILE * file) {

    cliente *temp = (cliente *) malloc(sizeof(cliente));

    fread(&temp->id, sizeof(temp->id), 1, file);
    fread(temp->nome, sizeof(temp->nome), 1, file);
    size_t read = fread(temp->nascimento, sizeof(temp->nascimento), 1, file);

    if(read == 0) return NULL;

    // Return
    return temp;
}

void cliente_to_stream(FILE * file, cliente * c) {
    fwrite(&c->id, sizeof(c->id), 1, file);
    fwrite(c->nome, sizeof(c->nome), 1, file);
    fwrite(c->nascimento, sizeof(c->nascimento), 1, file);
}

void cliente_show(cliente * c) {
    printf("\tID: %7d, Name: %10s, Birth: %s\n", c->id, c->nome, c->nascimento);
}

int id_comparator (cliente * a, cliente * b) {
    int p1 = ((cliente*) a)->id;
    int p2 = ((cliente*) b)->id;

    if(p1 > p2)
        return 1;
    else if(p1 == p2)
        return 0;
    else
        return -1;
}
