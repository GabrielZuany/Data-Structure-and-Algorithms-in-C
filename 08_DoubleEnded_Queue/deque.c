#include "deque.h"

struct Deque{
    CircularVector *cv;
};

Deque *deque_new(int define_total_capacity){
    Deque *d = (Deque*)malloc(sizeof(Deque));
    d->cv = dynamic_circular_vector_new(define_total_capacity);
    return d;
}

void deque_delete(Deque *d){
    circular_vector_free(d->cv);
    free(d);
}

void deque_push_front(Deque *d, int value){
    circular_vector_insert_into(d->cv, 0, value);
}

void deque_push_back(Deque *d, int value){
    circular_vector_push_back(d->cv, value);
}

void deque_pop_front(Deque *d){
    circular_vector_pop_front(d->cv);
}

void deque_pop_back(Deque *d){
    circular_vector_pop_back(d->cv);
}

int deque_get(Deque *d, int index){
    return circular_vector_get(d->cv, index);
}

void deque_print(Deque *d){
    circular_vector_print(d->cv);
}