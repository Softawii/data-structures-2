//
// Created by yancf on 26/06/2022.
//

#ifndef REPLACEMENTSELECTION_CLIENTE_H
#define REPLACEMENTSELECTION_CLIENTE_H

#include "../core/replacement_selection.h"
#include <stdio.h>

typedef struct{
    int id;
    char nome[50];
    char nascimento[11];
}cliente;


var  cliente_from_stream(FILE * file);
void cliente_to_stream(FILE * file, cliente * c);
void cliente_show(cliente * c);
int id_comparator (cliente * a, cliente * b);


#endif //REPLACEMENTSELECTION_CLIENTE_H

