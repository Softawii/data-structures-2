//
// Created by yancf on 02/07/2022.
//

#ifndef REPLACEMENTSELECTION_QUEUE_H
#define REPLACEMENTSELECTION_QUEUE_H

struct Queue;

typedef struct Queue Queue;

extern struct Queue* newQueue(int capacity);

extern int enqueue(struct Queue *q, void *value);

extern void* dequeue(struct Queue *q);

extern void freeQueue(struct Queue *q);

extern int queueSize(struct Queue *q);

#endif //REPLACEMENTSELECTION_QUEUE_H
