#include "item.h"
#include <stdio.h> 
#include <stdlib.h>

void sort(Item *a, int lo, int hi){
    for(int i = lo; i < hi; i++){
        for(int j = i + 1; j < hi; j++){
            if(less(a[j], a[i])){
                exch(a[i], a[j]);
            }
        }
    }
}