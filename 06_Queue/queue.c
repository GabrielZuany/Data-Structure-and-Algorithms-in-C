#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue{
    List *list;
};

Queue* create_queue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->list = list_construct();
    return q;
}

int queue_empty(Queue* q){
    return list_size(q->list) == 0;
}

int queue_size(Queue* q){
    return list_size(q->list);
}

void* queue_front(Queue* q){
    return list_get_first(q->list);
}

void* queue_back(Queue* q){
    return list_get_last(q->list);
}
void enqueue(Queue* q, void* data){
    list_push_back(q->list, data);
}

void dequeue(Queue* q){
    list_pop_front(q->list);
}

void queue_destroy(Queue* q){
    list_destroy(q->list);
    free(q);
}