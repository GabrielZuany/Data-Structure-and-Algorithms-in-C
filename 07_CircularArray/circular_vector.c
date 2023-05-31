#include "circular_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CircularVector {
    int *vector;
    int idx_front;
    int idx_rear;
    int size;
};

CircularVector *circular_vector_new() {
    CircularVector *cv = (CircularVector*)calloc(1, sizeof(CircularVector));
    cv->vector = (int*)calloc(sizeof(int), TOTAL_CAPACITY);
    cv->idx_front = 0;
    cv->idx_rear = 0;
    cv->size = 0;
    return cv;
}

void circular_vector_free(CircularVector *cv) {
    free(cv->vector);
    free(cv);
}

int circular_vector_size(CircularVector *cv) {
    return cv->size;
}

void circular_vector_push_back(CircularVector *cv, int value) {
    if(cv->size == 0){
      cv->vector[0] = value;
      cv->size++;
      return;
    }
    cv->idx_rear = (cv->idx_rear + 1) % TOTAL_CAPACITY;
    if(cv->idx_rear == cv->idx_front) {
        cv->idx_front = (cv->idx_front + 1);
        if(cv->idx_front == TOTAL_CAPACITY) {
            cv->idx_front = 0;
        }
    }
    if(cv->size < TOTAL_CAPACITY) {
        cv->size++;
    }
    cv->vector[cv->idx_rear] = value;
}

void circular_vector_pop_end_ptr(CircularVector *cv) {
    cv->vector[cv->idx_rear] = EMPTY;
    if (cv->idx_rear == 0) {
        cv->idx_rear = TOTAL_CAPACITY - 1;
    } else {
        cv->idx_rear--;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_pop_init_ptr(CircularVector *cv) {
    cv->vector[cv->idx_front] = EMPTY;
    if (cv->idx_front == TOTAL_CAPACITY - 1) {
        cv->idx_front--;
    }else {
        cv->idx_front++;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}
int circular_vector_get(CircularVector *cv, int index) {
    return cv->vector[index];
}

void circular_vector_print(CircularVector *cv) {
    printf("[");
    for(int i = 0; i < TOTAL_CAPACITY; i++) {
        if(circular_vector_get(cv, i) != EMPTY){
            printf("%d ", circular_vector_get(cv, i));
        }else{
            printf(" EMPTY ");
        }
    }
    printf("]\n");
}