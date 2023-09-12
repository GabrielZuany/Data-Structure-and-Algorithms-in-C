#include "item.h"
#include <stdio.h> 
#include <stdlib.h>

void sort(Item *a, int lo, int hi){
    for(int i = lo; i < hi; i++){
        int min = i;
        for(int j = i + 1; j < hi; j++){
            if(less(a[j], a[min])){
                min = j;
            }
        }
        exch(a[i], a[min]);
    }

}