#include "lib/vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Vector *vector_construct() {
  Vector *v = (Vector *)calloc(10, sizeof(Vector));
  v->size = 0;
  v->allocated = 10;
  v->data = (data_type *)calloc((v->allocated), sizeof(data_type *));
  return v;
}

void vector_destroy(Vector *v) {
  free(v->data);
  free(v);
}

void vector_push_back(Vector *v, data_type val) {
  int size = v->size;
  int allocated = v->allocated;

  if (allocated == size) {
    v->allocated *= 2;
    v->data = realloc(v->data, sizeof(data_type *) * allocated);
  }

  v->data[size] = val;

  v->size++;
}

int vector_size(Vector *v) { return v->size; }

data_type vector_get(Vector *v, int i) { return *(v->data + i); }

void vector_set(Vector *v, int i, data_type val) { *(v->data + i) = val; }

int vector_find(Vector *v, data_type val) {
  int length = v->size;
  int count;

  for (count = 0; count < length; count++) {
    if (*(v->data + count) == val) {
      return count;
    }
  }

  return -1;
}

data_type vector_remove(Vector *v, int i){
  int count = 0;
  int size = vector_size(v);
  data_type val = *(v->data+i);

  for(count=i; count<size; count++){
    *(v->data+count) = *(v->data+count+1);
  }
  v->size--;
  return val;
}

data_type vector_pop_front(Vector *v){
  return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v){
  return vector_remove(v, vector_size(v)-1);
}

void vector_insert(Vector *v, int i, data_type val){
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
  data_type temp;
  temp = *(v->data + i);
  *(v->data + i) = *(v->data + j);
  *(v->data + j) = temp;
}

//Not Bubble Sort
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

// Bubble sort
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

int vector_binary_search(Vector *v, data_type val){
  int size = vector_size(v);
  int max = size, min = 0;
  int middle_index = 0;

  middle_index = size;

  do{
    middle_index = min + (max-min)/2;

    if(*(v->data + middle_index) == val){
      return middle_index;
    }

    if (val < *(v->data + middle_index)){
      max = middle_index-1;
      continue;
    }

    if (val > *(v->data + middle_index)){
      min = middle_index+1;
      continue;
    }

  }while(min<=max);

  return -1;
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
  v_copy->data = calloc(sizeof(data_type), v->allocated);
  memcpy(v_copy->data, v->data, sizeof(data_type)*v->allocated);
  return v_copy;
}

void vector_clear(Vector *v){
  v->allocated = 0;
  v->size = 0;
  free(v->data);
  v->data = calloc(sizeof(data_type), 10);
}

int* vector_find_all(Vector *v, data_type val){
  int* idx = calloc(sizeof(data_type), v->size);
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