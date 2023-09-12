#include "item.h"
#include <stdio.h> 
#include <stdlib.h>

void sort(Item *a, int lo, int hi){
    int swapped = 0;
    
    for(int i = lo; i < hi/2; i++){
        swapped = 0;
        for(int j = i; j < hi - i - 1; j++){
            if(less(a[j], a[j+1])){
                exch(a[j], a[j+1]);
                swapped = 1;
            }
        }
        
        for(int k = hi - 2 - i; k > i; k--){
            if(high(a[k], a[k-1])){
                exch(a[k], a[k-1]);
                swapped = 1;
            } 
        }
        if(!swapped){
            break;
        }
    }
}
