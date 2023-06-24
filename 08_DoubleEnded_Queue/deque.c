#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 5
#define CHUNKS 5

typedef struct chunk {
    int* data_array;  // array of data
    int _size;        // actual size
    int idx_init;     // initial index
    int idx_end; 
} chunk;

typedef struct Deque {
    chunk* chunks;        // array of chunks
    int arr_chunks_size;  // array size
    int _tchunks;         // total chunks
    int size;             // deque size
    int allocated;        // total allocated
    int front_chunk_idx;        // front index
    int rear_chunk_idx;         // rear index
} Deque;


chunk chunk_create(int size) {
    chunk c;
    c.data_array = (int*) calloc(sizeof(int), size);
    c._size = 0;
    c.idx_init = 0;
    c.idx_end = 0;
    return c;
}

void chunk_push_front(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return;
    }
    if(c->idx_init == 0 && c->idx_end == 0){
        c->data_array[0] = data;
        c->idx_init--;
        c->idx_end = 1;
    }else if(c->idx_init >= 0 && c->idx_init < CHUNK_SIZE){
        c->data_array[c->idx_init] = data;
        c->idx_init--;
    }
    c->_size++;
}

void chunk_push_back(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return;
    }
    if(c->idx_init == 0 && c->idx_end == 0){
        c->data_array[0] = data;
        c->idx_init--;
        c->idx_end = 1;
    }else if(c->idx_end < CHUNK_SIZE && c->idx_end >= 0){
        c->data_array[c->idx_end] = data;
        c->idx_end++;
    }
    c->_size++;
}

int chunk_pop_front(chunk c) {
    if (c._size == 0) {
        return -1;
    }
    
    int data = c.data_array[c.idx_init];
    c.data_array[c.idx_init] = 0;
    
    if(c.idx_init == CHUNK_SIZE - 1)
        c.idx_init = 0;
    else
        c.idx_init++;
        
    c._size--;
    return data;
}

int chunk_pop_back(chunk c) {
    if (c._size == 0) {
        return -1;
    }
    
    int data = c.data_array[c.idx_end];
    c.data_array[c.idx_end] = 0;
    
    if(c.idx_end == 0)
        c.idx_end = CHUNK_SIZE - 1;
    else
        c.idx_end--;
        
    c._size--;
    return data;
}

int chunk_empty(chunk c) {
    return c._size == 0;
}

int chunk_size(chunk c) {
    return c._size;
}

int chunk_insert_last_position(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return -1;
    }

    if(c->idx_init == -1 && c->idx_end == 1){
        c->idx_init = 1;
    }else{
        c->idx_init = CHUNK_SIZE - 2;
    }
    c->idx_end = CHUNK_SIZE - 2;
      
    c->data_array[CHUNK_SIZE - 1] = data;
    c->_size++;
    return 0;
}

int chunk_insert_first_position(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return -1;
    }
    if(c->idx_init == 0 && c->idx_end == 0){
        c->idx_init = -1;
        c->idx_end = 1;
    }else{
        c->idx_end = 1;
    }
    
    c->data_array[0] = data;
    c->_size++;
    return 0;
}

void chunk_print(chunk c) {
    printf("[");
    for (int i = 0; i < 5; i++) {
        printf("%d | ", c.data_array[i]);
    }
    printf("]");
}

void chunk_destroy(chunk c) {
    free(c.data_array);
}

//------------------------------------------------


Deque* deque_create() {
    Deque* d = (Deque*) malloc(sizeof(Deque));
    d->chunks = (chunk*) malloc(sizeof(chunk) * CHUNKS);
    for(int i = 0; i < CHUNKS; i++){
        d->chunks[i] = chunk_create(CHUNK_SIZE);
    }
    d->_tchunks = CHUNKS * CHUNK_SIZE;
    d->size = 0;
    d->allocated = CHUNKS;
    d->front_chunk_idx = CHUNKS/2;
    d->rear_chunk_idx = CHUNKS/2;
    return d;
}

void deque_destroy(Deque* d) {
    for(int i = 0; i < CHUNKS; i++){
        chunk_destroy(d->chunks[i]);
    }
    free(d->chunks);
    free(d);
}

int deque_empty(Deque* d) {
    return d->size == 0;
}

void deque_push_front(Deque*d, int data){
    int curr_chunk_size = chunk_size(d->chunks[d->front_chunk_idx]);
    
    if(curr_chunk_size == CHUNK_SIZE || d->chunks[d->front_chunk_idx].idx_init < 0){
        int next_free_chunk = d->front_chunk_idx - 1;

        if(next_free_chunk == -1){
            next_free_chunk = CHUNKS - 1;
        }
        
        chunk_insert_last_position(&(d->chunks[next_free_chunk]), data);
        d->front_chunk_idx = next_free_chunk;
        
    }else{
        chunk_push_front(&(d->chunks[d->front_chunk_idx]), data); 
    }   
    d->size++;
}

void deque_push_back(Deque*d, int data){
    int curr_chunk_size = chunk_size(d->chunks[d->rear_chunk_idx]);

    if(curr_chunk_size == CHUNK_SIZE || d->chunks[d->rear_chunk_idx].idx_end == CHUNK_SIZE){
        int next_free_chunk = d->rear_chunk_idx + 1;

        if(next_free_chunk == CHUNKS){
            next_free_chunk = 0;
        }
            
        chunk_insert_first_position(&(d->chunks[next_free_chunk]), data);
        d->rear_chunk_idx = next_free_chunk;
    }else{
        chunk_push_back(&(d->chunks[d->rear_chunk_idx]), data);   
    }  
    d->size++;
}

void deque_print(Deque* d) {
    for (int i = 0; i < CHUNKS; i++) {
        printf("Chunk (%d): ", i);
        chunk_print(d->chunks[i]);
        printf("\n");
        }

        printf("front chunk idx: %d\n", d->front_chunk_idx);
        printf("front chunk init: %d\n", d->chunks[d->front_chunk_idx].idx_init);
        printf("front chunk end: %d\n", d->chunks[d->front_chunk_idx].idx_end);
        printf("front chunk size: %d\n", d->chunks[d->front_chunk_idx]._size);

        printf("rear chunk idx: %d\n", d->rear_chunk_idx);
        printf("rear chunk init: %d\n", d->chunks[d->rear_chunk_idx].idx_init);
        printf("rear chunk end: %d\n", d->chunks[d->rear_chunk_idx].idx_end);
        printf("rear chunk size: %d\n", d->chunks[d->rear_chunk_idx]._size);

        printf("\n");
    printf("\n");
}


int deque_pop_front(Deque* d){
    int data = -1;
    if(deque_empty(d)){
        return -1;
    }else{
        if(d->chunks[d->front_chunk_idx].idx_init + 1 >= CHUNK_SIZE){
            if(d->front_chunk_idx == CHUNKS - 1){
                d->front_chunk_idx = 0;
            }else{
                d->front_chunk_idx++;
            }
            int data_index = d->chunks[d->front_chunk_idx].idx_init;
            int chunk_index = d->front_chunk_idx;

            if(data_index == -1){
                data_index = 0;
            }
            data = d->chunks[chunk_index].data_array[data_index];
            d->chunks[chunk_index].data_array[data_index] = 0;
            d->chunks[chunk_index].idx_init = data_index;
            d->chunks[chunk_index]._size--;
            
        }else{
            data = d->chunks[d->front_chunk_idx].data_array[d->chunks[d->front_chunk_idx].idx_init+1];
            d->chunks[d->front_chunk_idx].data_array[d->chunks[d->front_chunk_idx].idx_init+1] = 0;
            d->chunks[d->front_chunk_idx].idx_init++;
            d->chunks[d->front_chunk_idx]._size--;
        }
    }
    d->size--;
    return data;
}


int deque_pop_back(Deque* d){
    int data = -1;
    if(deque_empty(d)){
        return -1;
    }else{
        if(d->chunks[d->rear_chunk_idx].idx_end - 1 == -1){
            if(d->rear_chunk_idx == 0){
                d->rear_chunk_idx = CHUNKS - 1;
            }else{
                d->rear_chunk_idx--;
            }
            int data_index = d->chunks[d->rear_chunk_idx].idx_end-1;
            int chunk_index = d->rear_chunk_idx;

            if(data_index >= CHUNK_SIZE){
                data_index = CHUNK_SIZE - 1;
            }else if(data_index == -1){
                data_index = 0;
            }

            data = d->chunks[chunk_index].data_array[data_index];
            d->chunks[chunk_index].data_array[data_index] = 0;
            d->chunks[chunk_index].idx_end = data_index;
            d->chunks[chunk_index]._size--;

        }else{
            data = d->chunks[d->rear_chunk_idx].data_array[d->chunks[d->rear_chunk_idx].idx_end-1];
            d->chunks[d->rear_chunk_idx].data_array[d->chunks[d->rear_chunk_idx].idx_end-1] = 0;
            d->chunks[d->rear_chunk_idx].idx_end--;
            d->chunks[d->rear_chunk_idx]._size--;
        }
    }
    d->size--;
    return data;
}
