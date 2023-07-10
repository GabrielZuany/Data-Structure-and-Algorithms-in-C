#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define CHUNK_SIZE 2
#define CHUNKS 1

typedef struct chunk {
    void** data_array;
    int _size;
    int idx_init;
    int idx_end;
} chunk;

chunk chunk_create(int size) {
    chunk c;
    c.data_array = (void**)calloc(size, sizeof(void*));
    c._size = 0;
    c.idx_init = 0;
    c.idx_end = 0;
    return c;
}

void chunk_push_front(chunk* c, void* data) {
    if (c->_size == CHUNK_SIZE) {
        return;
    }
    if(c->idx_init == 0 && c->_size == 0) {
        c->idx_end = 1;
    }
    c->data_array[c->idx_init] = data;
    c->idx_init--;
    c->_size++;
}

void chunk_push_back(chunk* c, void* data) 
{
    if (c->_size == CHUNK_SIZE) {
        return;
    }
     if(c->idx_end == 0) {
        c->idx_init = -1;
     }
    c->data_array[c->idx_end] = data;
    c->idx_end++;
    c->_size++;
}

void* chunk_pop_front(chunk* c)
{
    if (c->_size == 0) {
        return NULL;
    }
    void* data = c->data_array[c->idx_init + 1];
    c->data_array[c->idx_init + 1] = NULL;
    c->idx_init++;
    c->_size--;
    return data;
}

void* chunk_pop_back(chunk* c)
{
    if (c->_size == 0) {
        return NULL;
    }
    void* data = c->data_array[c->idx_end - 1];
    c->data_array[c->idx_end - 1] = NULL;
    c->idx_end--;
    c->_size--;
    return data;
}

int chunk_empty(chunk* c) {
    return c->_size == 0;
}

int chunk_size(chunk* c) {
    if(c == NULL) {
        return 0;
    }
    return c->_size;
}


//------------------------------------------------

typedef struct Deque {
    chunk* chunks;
    int arr_chunks_size; // size of the array of chunks
    int _tchunks;        // total chunks (1st arr)
    int size;            // deque size (chunks*size of each chunk)
    int front_chunk_idx;
    int rear_chunk_idx;
} Deque;

Deque* deque_create() {
    Deque* d = (Deque*)malloc(sizeof(Deque));
    d->chunks = (chunk*)malloc(sizeof(chunk) * CHUNKS);
    for (int i = 0; i < CHUNKS; i++) {
        d->chunks[i] = chunk_create(CHUNK_SIZE);
    }
    d->arr_chunks_size = CHUNKS;
    d->_tchunks = CHUNKS * CHUNK_SIZE;
    d->size = 0;
    d->front_chunk_idx = CHUNKS / 2;
    d->rear_chunk_idx = CHUNKS / 2;
    return d;
}

void __deque_realloc(Deque* d) {
    chunk* new_chunks = (chunk*)calloc(sizeof(chunk), (d->arr_chunks_size + 2));
    memmove(new_chunks + 1, d->chunks, sizeof(chunk) * d->arr_chunks_size);
    free(d->chunks);
    d->chunks = new_chunks;
    d->chunks[0] = chunk_create(CHUNK_SIZE);
    d->chunks[d->arr_chunks_size + 1] = chunk_create(CHUNK_SIZE);
    d->_tchunks = (d->arr_chunks_size + 2) * CHUNK_SIZE;
    d->arr_chunks_size += 2;
}

void __deque_reset(Deque *d){
    d->front_chunk_idx = d->arr_chunks_size / 2;
    d->rear_chunk_idx = d->arr_chunks_size / 2;
    for(int i = 0; i < d->arr_chunks_size; i++){
        d->chunks[i].idx_init = 0;
        d->chunks[i].idx_end = 0;
    }
}

void deque_push_front(Deque* d, void* data) {
    int curr_chunk_size = 0;

    if (curr_chunk_size == CHUNK_SIZE || d->chunks[d->front_chunk_idx].idx_init < 0) {
        int next_free_chunk = d->front_chunk_idx - 1;
        if (next_free_chunk == -1) {
            __deque_realloc(d);
            next_free_chunk = 0;
            d->rear_chunk_idx++;
        }
        d->front_chunk_idx = next_free_chunk;
        d->chunks[d->front_chunk_idx].idx_init = CHUNK_SIZE - 1;
        d->chunks[d->front_chunk_idx].idx_end = CHUNK_SIZE;
    }
    
    chunk_push_front(&(d->chunks[d->front_chunk_idx]), data);
    d->size++;
}

void deque_push_back(Deque* d, void* data) {
    int curr_chunk_size = 0;
    
    if (curr_chunk_size == CHUNK_SIZE || d->chunks[d->rear_chunk_idx].idx_end >= CHUNK_SIZE) {
        int next_free_chunk = d->rear_chunk_idx + 1;
        if (next_free_chunk == d->arr_chunks_size) {
            __deque_realloc(d);
            d->front_chunk_idx++;
            next_free_chunk = d->rear_chunk_idx + 2;
        }
        d->rear_chunk_idx = next_free_chunk;
        d->chunks[d->rear_chunk_idx].idx_init = 0;
        d->chunks[d->rear_chunk_idx].idx_end = 0;
    }

    chunk_push_back(&(d->chunks[d->rear_chunk_idx]), data);
    d->size++;
}

void* deque_pop_back(Deque* d){
    if (d->size == 0) {
        return NULL;
    }

    void* data = chunk_pop_back(&(d->chunks[d->rear_chunk_idx]));

    if(chunk_empty(&(d->chunks[d->rear_chunk_idx]))){
        d->rear_chunk_idx--;
    }
    if(d->rear_chunk_idx == -1){
        d->rear_chunk_idx = d->arr_chunks_size - 1;
    }
    
    d->size--;

    if(d->size == 0){
        __deque_reset(d);
    }
    return data;
}

void* deque_pop_front(Deque* d){
    if (d->size == 0) {
        return NULL;
    }

    void* data = chunk_pop_front(&(d->chunks[d->front_chunk_idx]));

    if(chunk_empty(&(d->chunks[d->front_chunk_idx]))){
        d->front_chunk_idx++;
    }
    if(d->front_chunk_idx == d->arr_chunks_size){
        d->front_chunk_idx = 0;
    }

    d->size--;

    if(d->size == 0){
        __deque_reset(d);
    }
    return data;
}

int deque_empty(Deque* d) {
    return d->size == 0;
}

void deque_destroy(Deque* d){
    if (d == NULL) {
        return;
    }
    for (int i = 0; i < d->arr_chunks_size; i++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            free(d->chunks[i].data_array[j]);
        }
        free(d->chunks[i].data_array);
    }
    free(d->chunks);

    free(d);
}