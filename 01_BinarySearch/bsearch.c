#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

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

int main() {
    Vector *v = vector_construct();
    int i;

    for (i = 5; i <= 80; i*=2) {
    vector_push_back(v, i);
    }

    printf("Vector: ");
    for (i = 0; i < vector_size(v); i++) {
    printf("%d | ", vector_get(v, i));
    }

    printf("\n");

    // vector is already sorted.
    printf("Index of 40: %d\n", vector_binary_search(v, 40));
    printf("Index of 25: %d\n", vector_binary_search(v, 25));

    vector_destroy(v);

  return 0;
}