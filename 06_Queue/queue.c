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

data_type queue_front(Queue* q){
    return list_get_first(q->list);
}

data_type queue_back(Queue* q){
    return list_get_last(q->list);
}
void queue_push_back(Queue* q, data_type data){
    list_push_back(q->list, data);
}

void queue_pop_front(Queue* q){
    list_pop_front(q->list);
}

void queue_queue_destroy(Queue* q){
    list_destroy(q->list);
    free(q);
}