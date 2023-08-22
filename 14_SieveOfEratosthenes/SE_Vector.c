#include <stdio.h>
#include <stdlib.h>
#include "../02_Vector/vector.h"
#include <math.h>

void print_int(void*n){
    int* v = (int*)n;
    printf("%d | ", *v);
}

void SieveOfEratosthenes_Vector(int n){
    Vector* v = vector_construct();
    int limit = sqrt(n);
    int* val = NULL;

    for(int i = 0; i < n; i++){
        val = (int*)calloc(sizeof(int), 1);
        *val = i;
        vector_push_back(v, val);
    }

    int current_idx = 2;
    int next_idx = 4;
    int* cell_value = NULL;

    for(int i = 0; i < n; i++){
        
        if(next_idx < n){
            cell_value = vector_get(v, next_idx);
            *cell_value = 0;
            vector_set(v, next_idx, cell_value);
            next_idx += current_idx;
        }
        
        if(next_idx >= n){
            do{
               current_idx++;
               if(current_idx >= n){
                   break;
               }

               cell_value = vector_get(v, current_idx); 
            }while(*cell_value == 0);

            next_idx = current_idx * 2;
            i = current_idx;
        }
    }
    for(int i = 0; i < n; i++){
        val = vector_pop_back(v);
        if(*val != 0){
            //printf("%d | ", *val);
        }
        free(val);
    }

    vector_destroy(v);
}

int main(){
    SieveOfEratosthenes_Vector(30);
    return 0;
}