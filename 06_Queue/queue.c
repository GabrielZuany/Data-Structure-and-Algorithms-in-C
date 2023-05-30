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

int empty(Queue* q){
    return list_size(q->list) == 0;
}

int size(Queue* q){
    return list_size(q->list);
}

data_type front(Queue* q){
    return list_get_first(q->list);
}

data_type back(Queue* q){
    return list_get_last(q->list);
}
void push_back(Queue* q, data_type data){
    list_push_back(q->list, data);
}

void pop_front(Queue* q){
    list_pop_front(q->list);
}

void queue_destroy(Queue* q){
    list_destroy(q->list);
    free(q);
}