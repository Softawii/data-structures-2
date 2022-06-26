//
// Created by yancf on 26/06/2022.
//

#ifndef REPLACEMENTSELECTION_CLIENTE_H
#define REPLACEMENTSELECTION_CLIENTE_H

#include "../src/core.h"
#include <stdio.h>

typedef struct{
    int id;
    char nome[50];
    char nascimento[11];
}cliente;


var  cliente_from_stream(FILE * file) {

    long curr = ftell(file);
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, curr, SEEK_SET);

    if(ftell(file) < size) {
        cliente *temp = (cliente *) malloc(sizeof(cliente));

        fread(&temp->id, sizeof(temp->id), 1, file);
        fread(temp->nome, sizeof(temp->nome), 1, file);
        fread(temp->nascimento, sizeof(temp->nascimento), 1, file);
        // Return
        return temp;
    }
    return NULL;
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


#endif //REPLACEMENTSELECTION_CLIENTE_H
