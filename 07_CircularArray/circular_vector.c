#include "circular_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CircularVector {
    void **vector;
    int idx_front;
    int idx_rear;
    int size;
    int allocated;
};

Bool g_static_vector = true;

CircularVector *circular_vector_new(int define_total_capacity) {
    if(define_total_capacity == null){
        define_total_capacity = DEFAULT_CAPACITY;
    }
    CircularVector *cv = (CircularVector*)calloc(1, sizeof(CircularVector));
    cv->vector = (void**)calloc(sizeof(void*), define_total_capacity);
    cv->idx_front = 0;
    cv->idx_rear = 0;
    cv->size = 0;
    cv->allocated = define_total_capacity;
    return cv;
}

CircularVector* static_circular_vector_new(int define_total_capacity){
    g_static_vector = true;
    return circular_vector_new(define_total_capacity);
}

CircularVector *dynamic_circular_vector_new(int define_total_capacity){
    g_static_vector = false;
    return circular_vector_new(define_total_capacity);
}

void circular_vector_clear(CircularVector* cv){
    cv->idx_front = 0;
    cv->idx_rear = 0;
    cv->size = 0;
    memset(cv->vector, 0, sizeof(int)*cv->allocated);
}

void circular_vector_default(CircularVector* cv){
    cv->vector = (void**)realloc(cv->vector, sizeof(void*)*DEFAULT_CAPACITY);
    memset(cv->vector, 0, sizeof(void*)*DEFAULT_CAPACITY);
    cv->allocated = DEFAULT_CAPACITY;
    cv->idx_front = 0;
    cv->idx_rear = 0;
    cv->size = 0;
}

void *circular_vector_realloc(CircularVector *cv){
    void** cpy = (void**)calloc(sizeof(void*), 2*cv->allocated);
    memmove(cpy, cv->vector, sizeof(void*)*cv->allocated);
    free(cv->vector);
    cv->vector = cpy;
    cv->allocated *= 2;
    circular_vector_fix_init_ptr(cv);
    circular_vector_fix_end_ptr(cv);
}

void circular_vector_free(CircularVector *cv) {
    free(cv->vector);
    free(cv);
}

int circular_vector_size(CircularVector *cv) {
    return cv->size;
}

void circular_vector_push_back(CircularVector *cv, void* value) {
    if(cv->size == cv->allocated && !g_static_vector){
        circular_vector_realloc(cv);
    }

    if(cv->size == 0){
      cv->vector[0] = value;
      cv->size++;
      return;
    }
    cv->idx_rear = (cv->idx_rear + 1) % cv->allocated;
    if(cv->idx_rear == cv->idx_front) {
        cv->idx_front = (cv->idx_front + 1);
        if(cv->idx_front == cv->allocated) {
            cv->idx_front = 0;
        }
    }
    cv->vector[cv->idx_rear] = value;
    cv->size++;
}

void circular_vector_push_front(CircularVector *cv, void* value) {
    if(cv->size == cv->allocated && !g_static_vector){
        circular_vector_realloc(cv);
    }

    if(cv->size == 0){
      cv->vector[0] = value;
      cv->size++;
      return;
    }
    cv->idx_front = (cv->idx_front - 1 + cv->allocated) % cv->allocated;
    if(cv->idx_front == cv->idx_rear) {
        cv->idx_rear = ((cv->idx_rear - 1 + cv->allocated) % cv->allocated);
    }
    cv->vector[cv->idx_front] = value;
    cv->size++;
}

void circular_vector_pop_end_ptr(CircularVector *cv) {
    cv->vector[cv->idx_rear] = NULL;
    if(cv->idx_rear - 1 < 0) {
        cv->idx_rear = cv->allocated - 1;
    } else {
        cv->idx_rear--;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_pop_init_ptr(CircularVector *cv) {
    cv->vector[cv->idx_front] = NULL;
    if(cv->idx_front + 1 == cv->allocated) {
        cv->idx_front = 0;
    } else {
        cv->idx_front++;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_pop_index(CircularVector *cv, int index) {
    cv->vector[index] = NULL;
    if(cv->size > 0) {
        cv->size--;
    }
    if(index == cv->idx_front) {
        circular_vector_pop_init_ptr(cv);
    } else if(index == cv->idx_rear) {
        circular_vector_pop_end_ptr(cv);
    }
}

void circular_vector_fix_end_ptr(CircularVector *cv) {
    cv->idx_rear = cv->size - 1;
}

void circular_vector_fix_init_ptr(CircularVector *cv) {
    cv->idx_front = 0;
}

void* circular_vector_get(CircularVector *cv, int index) {
    return cv->vector[index];
}

void circular_vector_print(CircularVector *cv, void(*printfn)(void*)) {
    printf("[");
    for(int i = 0; i < cv->allocated; i++) {
        printfn(circular_vector_get(cv, i));
    }
    printf("]\n");
}