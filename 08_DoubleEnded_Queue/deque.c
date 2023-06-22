#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 5
#define CHUNKS 5

typedef struct chunk {
    int* data_array; // array of data
    int _size;        // actual size
    int idx_init;    // initial index
    int idx_end; 
} chunk;

typedef struct Deque {
    chunk* chunks;        // array of chunks
    int arr_chunks_size;  // array size
    int _tchunks;         // total chunks
    int size;             // deque size
    int allocated;        // total allocated
    chunk* _front;        // front chunk
    chunk* _rear;         // rear chunk
    int front_idx;        // front index
    int rear_idx;         // rear index
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
   
    if(c->idx_init == 0){
        c->data_array[c->idx_init] = data;
        c->idx_init = CHUNK_SIZE - 1;
    }
    else{
        c->data_array[c->idx_init] = data;
        c->idx_init--;
        
    }
    c->_size++;
}

void chunk_push_back(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return;
    }
    
    if(c->idx_end == CHUNK_SIZE - 1){
        c->data_array[c->idx_end] = data;
        c->idx_end = 0;
    }
    else{
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

    c->idx_init = CHUNK_SIZE - 2;
    c->idx_end = 0;
      
    c->data_array[CHUNK_SIZE - 1] = data;
    c->_size++;
    return 0;
}

int chunk_insert_first_position(chunk* c, int data) {
    if (c->_size == CHUNK_SIZE) {
        return -1;
    }
    c->idx_init = 0;
    c->idx_end = 1;
    
        
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
    d->_front = NULL;
    d->_rear = NULL;
    d->front_idx = CHUNKS/2;
    d->rear_idx = CHUNKS/2;
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
    int curr_chunk_size = chunk_size(d->chunks[d->front_idx]);
    
    if(curr_chunk_size == CHUNK_SIZE){
        printf("NOT THERE\n");
        int next_free_chunk = d->front_idx - 1;

        if(next_free_chunk == -1){
            next_free_chunk = CHUNKS - 1;
        }
            
        chunk_insert_last_position(&(d->chunks[next_free_chunk]), data);
        d->front_idx = next_free_chunk;
        
    }else{
        printf("HERE\n");
        chunk_push_front(&(d->chunks[d->front_idx]), data); 
    }   
}

void deque_push_back(Deque*d, int data){
    int curr_chunk_size = chunk_size(d->chunks[d->rear_idx]);

    if(curr_chunk_size == CHUNK_SIZE){
        int next_free_chunk = d->rear_idx + 1;

        if(next_free_chunk == CHUNKS){
            next_free_chunk = 0;
        }
            
        chunk_insert_first_position(&(d->chunks[next_free_chunk]), data);

        d->rear_idx = next_free_chunk;
    }else{
       chunk_push_back(&(d->chunks[d->rear_idx]), data); 
    }   
}

void deque_print(Deque* d) {
    for (int i = 0; i < CHUNKS; i++) {
        printf("Chunk (%d): ", i);
        chunk_print(d->chunks[i]);
        printf("\n");
    }
    printf("\n");
}