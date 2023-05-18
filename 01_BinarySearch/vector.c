#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Vector{
  data_type *data;
  int size;
  int allocated;
};

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

int vector_size(Vector *v) { 
  return v->size; 
}

data_type vector_get(Vector *v, int i) {
  return *(v->data + i);
}
