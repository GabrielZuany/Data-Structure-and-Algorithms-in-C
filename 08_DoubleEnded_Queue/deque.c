#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define CHUNK_SIZE 1
#define CHUNKS 5

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
    if (c->idx_init == 0 && c->idx_end == 0) {
        c->data_array[0] = data;
        c->idx_init--;
        c->idx_end = 1;
    }
    else if (c->idx_init >= 0 && c->idx_init < CHUNK_SIZE) {
        c->data_array[c->idx_init] = data;
        c->idx_init--;
    }
    c->_size++;
}

void chunk_push_back(chunk* c, void* data) {
    if (c->_size == CHUNK_SIZE) {
        return;
    }
    if (c->idx_init == 0 && c->idx_end == 0) {
        c->data_array[0] = data;
        c->idx_init--;
        c->idx_end = 1;
    }
    else if (c->idx_end < CHUNK_SIZE && c->idx_end >= 0) {
        c->data_array[c->idx_end] = data;
        c->idx_end++;
    }
    c->_size++;
}

void* chunk_pop_front(chunk* c) {
    if (c->_size == 0) {
        return NULL;
    }

    void* data = c->data_array[c->idx_init];
    c->data_array[c->idx_init] = NULL;

    if (c->idx_init == CHUNK_SIZE - 1)
        c->idx_init = 0;
    else
        c->idx_init++;

    c->_size--;
    return data;
}

void* chunk_pop_back(chunk* c) {
    if (c->_size == 0) {
        return NULL;
    }

    void* data = c->data_array[c->idx_end];
    c->data_array[c->idx_end] = NULL;

    if (c->idx_end == 0)
        c->idx_end = CHUNK_SIZE - 1;
    else
        c->idx_end--;

    c->_size--;
    return data;
}

int chunk_empty(chunk* c) {
    return c->_size == 0;
}

int chunk_size(chunk* c) {
    return c->_size;
}

int chunk_insert_last_position(chunk* c, void* data) {
    if (c->_size == CHUNK_SIZE) {
        return -1;
    }

    if (c->idx_init == -1 && c->idx_end == 1) {
        c->idx_init = 1;
    }
    else {
        c->idx_init = CHUNK_SIZE - 2;
    }
    c->idx_end = CHUNK_SIZE - 2;

    c->data_array[CHUNK_SIZE - 1] = data;
    c->_size++;
    return 0;
}

int chunk_insert_first_position(chunk* c, void* data) {
    if (c->_size == CHUNK_SIZE) {
        return -1;
    }
    if (c->idx_init == 0 && c->idx_end == 0) {
        c->idx_init = -1;
        c->idx_end = 1;
    }
    else {
        c->idx_end = 1;
    }

    c->data_array[0] = data;
    c->_size++;
    return 0;
}

void chunk_destroy(chunk* c) {
    for(int i = 0; i < CHUNK_SIZE; i++) {
        free(c->data_array[i]);
    }
    free(c->data_array);
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

void deque_push_front(Deque* d, void* data) {
    int curr_chunk_size = chunk_size(&(d->chunks[d->front_chunk_idx]));

    if (curr_chunk_size == CHUNK_SIZE || d->chunks[d->front_chunk_idx].idx_init < 0) {
        int next_free_chunk = d->front_chunk_idx - 1;

        if (next_free_chunk == -1) {
            //next_free_chunk = CHUNKS - 1;
            chunk* new_chunks = (chunk*)calloc(sizeof(chunk), (d->arr_chunks_size + 2));
            memcpy(new_chunks + 1, d->chunks, sizeof(chunk) * d->arr_chunks_size);
            __deque_destroy_chunks(d);
            free(d->chunks);
            d->chunks = new_chunks;
            d->chunks[0] = chunk_create(CHUNK_SIZE);
            d->chunks[d->arr_chunks_size + 1] = chunk_create(CHUNK_SIZE);
            d->_tchunks = (d->arr_chunks_size + 2) * CHUNK_SIZE;
            d->arr_chunks_size += 2;
            
            //reindex chunks
            for (int i = 0; i < d->arr_chunks_size; i++) {
                d->chunks[i].idx_init += 1;
                d->chunks[i].idx_end += 1;
            }

            next_free_chunk = 0;
        }
        chunk_insert_last_position(&(d->chunks[next_free_chunk]), data);
        d->front_chunk_idx = next_free_chunk;
    }
    else {
        chunk_push_front(&(d->chunks[d->front_chunk_idx]), data);
    }
    d->size++;
}

void deque_push_back(Deque* d, void* data) {
    int curr_chunk_size = chunk_size(&(d->chunks[d->rear_chunk_idx]));

    if (curr_chunk_size == CHUNK_SIZE || d->chunks[d->rear_chunk_idx].idx_end == CHUNK_SIZE) {
        int next_free_chunk = d->rear_chunk_idx + 1;

        if (next_free_chunk == CHUNKS) {
            next_free_chunk = 0;
        }

        chunk_insert_first_position(&(d->chunks[next_free_chunk]), data);
        d->rear_chunk_idx = next_free_chunk;
    }
    else {
        chunk_push_back(&(d->chunks[d->rear_chunk_idx]), data);
    }
    d->size++;
}

void* deque_pop_front(Deque* d) {
    void* data = NULL;
    if (deque_empty(d)) {
        return NULL;
    }
    else {
        if (d->chunks[d->front_chunk_idx].idx_init + 1 >= CHUNK_SIZE) {
            if (d->front_chunk_idx == CHUNKS - 1) {
                d->front_chunk_idx = 0;
            }
            else {
                d->front_chunk_idx++;
            }
            int data_index = d->chunks[d->front_chunk_idx].idx_init;
            int chunk_index = d->front_chunk_idx;

            if (data_index == -1) {
                data_index = 0;
            }
            data = d->chunks[chunk_index].data_array[data_index];
            d->chunks[chunk_index].data_array[data_index] = NULL;
            d->chunks[chunk_index].idx_init = data_index;
            d->chunks[chunk_index]._size--;

        }
        else {
            data = d->chunks[d->front_chunk_idx].data_array[d->chunks[d->front_chunk_idx].idx_init + 1];
            d->chunks[d->front_chunk_idx].data_array[d->chunks[d->front_chunk_idx].idx_init + 1] = NULL;
            d->chunks[d->front_chunk_idx].idx_init++;
            d->chunks[d->front_chunk_idx]._size--;
        }
    }
    d->size--;
    return data;
}

void* deque_pop_back(Deque* d) {
    void* data = NULL;
    if (deque_empty(d)) {
        return NULL;
    }
    else {
        if (d->chunks[d->rear_chunk_idx].idx_end - 1 < 0) {
            if (d->rear_chunk_idx == 0) {
                d->rear_chunk_idx = CHUNKS - 1;
            }
            else {
                d->rear_chunk_idx--;
            }
            int data_index = d->chunks[d->rear_chunk_idx].idx_end - 1;
            int chunk_index = d->rear_chunk_idx;

            if (data_index >= CHUNK_SIZE) {
                data_index = CHUNK_SIZE - 1;
            }
            else if (data_index == -1) {
                data_index = 0;
            }

            data = d->chunks[chunk_index].data_array[data_index];
            d->chunks[chunk_index].data_array[data_index] = NULL;
            d->chunks[chunk_index].idx_end = data_index + 1;
            d->chunks[chunk_index]._size--;
        }
        else {
            data = d->chunks[d->rear_chunk_idx].data_array[d->chunks[d->rear_chunk_idx].idx_end - 1];
            d->chunks[d->rear_chunk_idx].data_array[d->chunks[d->rear_chunk_idx].idx_end - 1] = NULL;
            d->chunks[d->rear_chunk_idx].idx_end--;
            d->chunks[d->rear_chunk_idx]._size--;
        }
    }
    d->size--;
    return data;
}

int deque_empty(Deque* d) {
    return d->size == 0;
}

void __deque_destroy_chunks(Deque* d) {
    for (int i = 0; i < d->arr_chunks_size; i++) {
        chunk_destroy(&(d->chunks[i]));
    }
}

void deque_destroy(Deque* d) {
    __deque_destroy_chunks(d);
    free(d->chunks);
    free(d);
}
