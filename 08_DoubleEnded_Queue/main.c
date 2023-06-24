#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(){
    Deque* d = deque_create();

    for(int i = 0; i<13; i++){
        deque_push_front(d, i + 1);
        deque_print(d);
    }

    for(int i = 0; i<12; i++){
        deque_push_back(d, i + 1);
        deque_print(d);
    }

    printf("=========\n\n\nPOP:\n");
    for(int i = 0; i<13; i++){
        printf(">>>%d\n",deque_pop_back(d));
        deque_print(d);
    }
    for(int i = 0; i<12; i++){
        printf(">>>%d\n",deque_pop_front(d));
        deque_print(d);
    }
    
    deque_destroy(d);
    return 0;
}