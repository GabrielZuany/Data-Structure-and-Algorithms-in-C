#include <stdio.h>
#include <stdlib.h>

int binary_search(void *arr, int arr_size, int elem_size, int (*cmp)(void *, void *), void *elem) {
  int max = arr_size, min = 0;
  int middle_index = 0;
  middle_index = arr_size;

  do{
    middle_index = min + (max-min)/2;

    if(cmp(arr + middle_index*elem_size, elem) == 0){
      return middle_index;
    }
    if (cmp(arr + middle_index*elem_size, elem) == 1){
      max = middle_index-1;
      continue;
    }
    if (cmp(arr + middle_index*elem_size, elem) == -1){
      min = middle_index+1;
      continue;
    }
  }while(min<=max);

  return -1;
}
