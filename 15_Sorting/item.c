#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Item ITEMrand(){
    return rand() % 1000;
}

Item init(int n){
    return n;
}

void ITEMshow(Item i){
    printf("%d\n", i);
}