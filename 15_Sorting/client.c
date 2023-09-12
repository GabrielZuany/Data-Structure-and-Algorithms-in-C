#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include <time.h>

extern void sort(Item *a, int lo, int hi);

int main(int argc, char** argv){
    int n = 6;
    srand(time(NULL));

    Item* arr = malloc(n * sizeof(Item));
    for(int i = 0; i < n; i++){
        Item item = ITEMrand();
        arr[i] = item;
    }
    for(int i = 0; i < n; i++){
        ITEMshow(arr[i]);
    }
    printf("\n");

    sort(arr, 0, n);

    for(int i = 0; i < n; i++){
        ITEMshow(arr[i]);
    }

    free(arr);
    return 0;
}