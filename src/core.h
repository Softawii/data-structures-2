//
// Created by yancf on 26/06/2022.
//

#ifndef REPLACEMENTSELECTION_CORE_H
#define REPLACEMENTSELECTION_CORE_H

// #define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef void * var;
typedef var  (from_stream)(FILE *);
typedef void (to_stream)  (FILE *, var);
typedef int  (comparator) (var, var);
typedef void (show)       (var);

typedef enum STATE {
    FREEZE   = 0,
    ENABLED  = 1,
    NULLABLE = 2
} STATE;


typedef struct {
    var    value;
    STATE status;
} var_status;


bool all_freeze(var_status * elements, int64_t length) {
    for(int64_t index = 0; index < length; index++) if(elements[index].status == ENABLED) return false;
    return true;
}

void unfreeze(var_status * elements, int64_t length) {
    for(int64_t index = 0; index < length; index++) {
        if(elements[index].status == FREEZE) elements[index].status = ENABLED;
    }
}

bool all_nullable(var_status * elements, int64_t length) {
    for(int64_t index = 0; index < length; index++) if(elements[index].status != NULLABLE) return false;
    return true;
}

var_status * min(var_status * elements, int64_t length, comparator comp) {

    var_status * temp = NULL;

    for(int64_t index = 0; index < length; index++) {
        // We Want Just Enabled Elements
        if(elements[index].status != ENABLED) continue;

        if(temp == NULL) {
            temp = &elements[index];
        } else {
            if(comp(temp->value, elements[index].value) > 0) {
                temp = &elements[index];
            }
        }
    }
    return temp;
}

void generate_partitions(int64_t number_of_registries, char * input_file, from_stream from, to_stream to, comparator comp, show show) {

    FILE * source;
    FILE * target;
    var    last = NULL;
    int    partition_number = 0;
    char   output_file[50];

    if ((source = fopen(input_file, "rb")) == NULL) {
        printf("partitions: Erro ao abrir arquivo de origem\n");
        exit(1);
    }

    var_status * elements = (var_status *)(malloc(number_of_registries * sizeof(var_status)));

    // Populate the array
    for(int64_t index = 0; index < number_of_registries; index++) {
        elements[index].value  = from(source);
        elements[index].status = elements[index].value == NULL ? NULLABLE : ENABLED;
    }

    while(!all_nullable(elements, number_of_registries)) {
        sprintf(output_file, "partition_%d.dat", partition_number);
        partition_number += 1;
        last = NULL;
        unfreeze(elements, number_of_registries);

        #ifdef DEBUG
        printf("Creating Partition %s\n", output_file);
        #endif
        // Creating File
        if ((target = fopen(output_file, "wb")) == NULL) {
            printf("partitions: Erro ao abrir arquivo\n");
            exit(1);
        }

        while (!all_freeze(elements, number_of_registries)) {
            var_status *temp = min(elements, number_of_registries, comp);

            if (temp == NULL) {
                printf("partitions: erro inesperado!");
                exit(1);
            }

            // Flux of Start
            if (last == NULL) {
                // Write it without comparing
                to(target, temp->value);

                #ifdef DEBUG
                printf("\tWrote in File: ");
                show(temp->value);
                #endif

                // The New Last
                last = temp->value;
            } else {
                // Need to compare to the last
                // Last > Temp ? Freeze It
                if (comp(last, temp->value) > 0) {
                    temp->status = FREEZE;
                    continue;
                } else {
                    // Write!
                    to(target, temp->value);

                    #ifdef DEBUG
                    printf("\tWrote in File: ");
                    show(temp->value);
                    #endif

                    // Free the Last (we don't need memory leaks)
                    free(last);

                    // Replace the Last
                    last = temp->value;
                }
            }

            // Replacing the position
            var aux = from(source);

            // Fail to Read (EOF)
            if (aux == NULL) {
                temp->value = NULL;
                temp->status = NULLABLE;
            } else {
                temp->value = aux;
            }
        }
        fclose(target);
    }
    fclose(source);
}


#endif //REPLACEMENTSELECTION_CORE_H
