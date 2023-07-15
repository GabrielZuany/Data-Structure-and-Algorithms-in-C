#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Vector{
  void **data;
  int size;
  int allocated;
};

Vector *vector_construct() {
  Vector *v = (Vector *)calloc(INITIAL_CAPACITY, sizeof(Vector));
  v->size = 0;
  v->allocated = INITIAL_CAPACITY;
  v->data = (void **)calloc((v->allocated), sizeof(void*));
  return v;
}

void vector_destroy(Vector *v) {
  free(v->data);
  free(v);
}

void vector_push_back(Vector *v, void* val) {
  int size = v->size;
  int allocated = v->allocated;

  if (allocated == size) {
    v->allocated *= 2;
    v->data = realloc(v->data, sizeof(void *) * allocated);
  }

  v->data[size] = val;
  v->size++;
}

int vector_size(Vector *v) { 
  return v->size;
}

void* vector_get(Vector *v, int i) {
    return *(v->data + i); 
}

void vector_set(Vector *v, int i, void* val) {
  *(v->data + i) = val;
}

int vector_find(Vector *v, void* val) {
  int length = v->size;
  int count;

  for (count = 0; count < length; count++) {
    if (*(v->data + count) == val) {
      return count;
    }
  }

  return -1;
}

void* vector_remove(Vector *v, int i){
  int count = 0;
  int size = vector_size(v);
  void* val = *(v->data+i);

  for(count=i; count<size; count++){
    *(v->data+count) = *(v->data+count+1);
  }
  v->size--;
  return val;
}

void* vector_pop_front(Vector *v){
  return vector_remove(v, 0);
}

void* vector_pop_back(Vector *v){
  return vector_remove(v, vector_size(v)-1);
}

void vector_insert(Vector *v, int i, void* val){
  int last_position = vector_size(v) - 1;
  int count = 0;

  if(v->size+1 > v->allocated){
    v->data = realloc(v->data, v->allocated*2);
    v->allocated*=2;
  }

  for(count=last_position+1; count>i; count--){
    *(v->data + count) = *(v->data + count -1);
  }

  *(v->data + i) = val;

  v->size=vector_size(v) + 1;
}

void vector_swap(Vector *v, int i, int j){
  void* temp;
  temp = *(v->data + i);
  *(v->data + i) = *(v->data + j);
  *(v->data + j) = temp;
}

void vector_sort(Vector *v){
  int size = vector_size(v);
  int count_i = 0, count_j = 0, swapped = 0, swapped_counter = 0;

  for(count_i=0; count_i<size; count_i++){

    for(count_j=count_i+1; count_j<size; count_j++){

      if( *(v->data + count_i) > *(v->data + count_j) ){
        vector_swap(v, count_i, count_j);
        swapped = 1;
        swapped_counter++;
        continue;
      }

      if( count_j == size-1 && swapped == 0){
        return;
      }
    }
    swapped = 0;
  }

}

void vector_bubble_sort(Vector *v){
  int size = vector_size(v);
  int count = 0, swapped = 0;

  do{
    swapped = 0;

    for(count=0; count<size-1; count++){

      if( *(v->data + count) > *(v->data + count +1) ){
        vector_swap(v, count, count+1);
        swapped = 1;
      }
      
    }
  }while(swapped);
}

int _compare(const void* a, const void* b){
  return (*(int*)a - *(int*)b);
}

int vector_binary_search(Vector *v, void* val){
  return *(int*)bsearch(val, v->data, v->size, sizeof(void*), _compare);
}

void vector_reverse(Vector *v){
  int size = vector_size(v);
    int low = 0, high = size-1;
    int middle = (low + (high-low)/2);

  while(low<=middle){
    vector_swap(v, low, high);
    low++;
    high--;
  }
}

Vector *vector_copy(Vector *v){
  Vector* v_copy = malloc(sizeof(Vector));
  v_copy->size = v->size;
  v_copy->allocated = v->allocated;
  v_copy->data = calloc(sizeof(void*), v->allocated);
  memcpy(v_copy->data, v->data, sizeof(void*)*v->allocated);
  return v_copy;
}

void vector_clear(Vector *v){
  v->allocated = 0;
  v->size = 0;
  free(v->data);
  v->data = calloc(sizeof(void*), INITIAL_CAPACITY);
}

int* vector_find_all(Vector *v, void* val){
  int* idx = calloc(sizeof(void*), v->size);
  int idx_count = 0;
  int count = 0, size = vector_size(v);

  for(count=0; count<size; count++){
    if(val == *(v->data+count)){
      *(idx + idx_count) = count;
      idx_count++;
    }
  }
  return idx;
}

void vector_print(Vector *v, void (*printfn)(void*)){
  int count = 0, size = vector_size(v);

  for(count=0; count<size; count++){
    printfn(*(v->data+count));
  }
  printf("\n");
}
