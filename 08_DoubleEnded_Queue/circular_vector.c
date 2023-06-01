#include "circular_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CircularVector {
    int *vector;
    int idx_front;
    int idx_rear;
    int size;
    int allocated;
};

CircularVector *circular_vector_new() {
    CircularVector *cv = (CircularVector*)calloc(1, sizeof(CircularVector));
    cv->vector = (int*)calloc(sizeof(int), TOTAL_CAPACITY);
    cv->idx_front = 0;
    cv->idx_rear = 0;
    cv->size = 0;
    cv->allocated = TOTAL_CAPACITY;
    return cv;
}

void *circular_vector_realloc(CircularVector *cv){
    cv->vector = (int*)realloc(cv->vector, sizeof(int) * (cv->allocated*2));
    cv->allocated *= 2;
}

void circular_vector_free(CircularVector *cv) {
    free(cv->vector);
    free(cv);
}

int circular_vector_size(CircularVector *cv) {
    return cv->size;
}

int circular_vector_allocated(CircularVector *cv) {
    return cv->allocated;
}

void circular_vector_push_back(CircularVector *cv, int value) {
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
    if(cv->size < cv->allocated) {
        cv->size++;
    }
    cv->vector[cv->idx_rear] = value;
}

void circular_vector_push_front(CircularVector *cv, int value) {
    if(cv->size == 0){
        cv->vector[0] = value;
        cv->idx_front = 0;
        cv->size++;
      return;
    }
    if(cv->idx_front == 0) {
        cv->idx_front = cv->allocated - 1;
        cv->idx_front = cv->allocated - 1;
        cv->size++;
        return;
    }
    cv->idx_front = (cv->idx_front - 1 + cv->allocated) % cv->allocated;
    if(cv->idx_front == cv->idx_rear) {
        cv->idx_rear = (cv->idx_rear - 1 + cv->allocated) % cv->allocated;
    }
    cv->vector[cv->idx_front] = value;
    cv->size++;
}

void circular_vector_pop_end_ptr(CircularVector *cv) {
    cv->vector[cv->idx_rear] = EMPTY;
    if (cv->idx_rear == 0) {
        cv->idx_rear = cv->allocated - 1;
    } else {
        cv->idx_rear--;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_pop_init_ptr(CircularVector *cv) {
    cv->vector[cv->idx_front] = EMPTY;
    if (cv->idx_front == cv->allocated - 1) {
        cv->idx_front--;
    }else {
        cv->idx_front++;
    }
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_pop_index(CircularVector *cv, int index) {
    cv->vector[index] = EMPTY;
    if(cv->size > 0) {
        cv->size--;
    }
}

void circular_vector_fix_end_ptr(CircularVector *cv) {
    cv->idx_rear = cv->size - 1;
}

void circular_vector_fix_init_ptr(CircularVector *cv) {
    cv->idx_front = 0;
}

int circular_vector_get(CircularVector *cv, int index) {
    return cv->vector[index];
}

void circular_vector_print(CircularVector *cv) {
    printf("[");
    for(int i = 0; i < cv->allocated; i++) {
        if(circular_vector_get(cv, i) != EMPTY){
            printf("%d ", circular_vector_get(cv, i));
        }
    }
    printf("]\n");
}