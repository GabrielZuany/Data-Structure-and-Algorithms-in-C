#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Deque {
    CircularVector *c_vector;
};

Deque *deque_new() {
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    deque->c_vector = circular_vector_new();
    return deque;
}

void deque_delete(Deque *deque) {
    circular_vector_free(deque->c_vector);
    free(deque);
}

int deque_size(Deque *deque) {
    return circular_vector_size(deque->c_vector);
}

int deque_get(Deque *deque, int index) {
    return circular_vector_get(deque->c_vector, index);
}

void deque_push_front(Deque *deque, int value) {
    if(deque_size(deque) == circular_vector_allocated(deque->c_vector)) {
        circular_vector_realloc(deque->c_vector);
        circular_vector_fix_init_ptr(deque->c_vector);
    }
    circular_vector_push_front(deque->c_vector, value);
}

void deque_push_back(Deque *deque, int value) {
    if(deque_size(deque) == circular_vector_allocated(deque->c_vector)) {
        circular_vector_realloc(deque->c_vector);
        circular_vector_fix_end_ptr(deque->c_vector);
    }
    circular_vector_push_back(deque->c_vector, value);
}

void deque_pop_front(Deque *deque) {
    circular_vector_pop_init_ptr(deque->c_vector);
}

void deque_pop_back(Deque *deque) {
    circular_vector_pop_end_ptr(deque->c_vector);
}

void deque_print(Deque *deque) {
    circular_vector_print(deque->c_vector);
}
