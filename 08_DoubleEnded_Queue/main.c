// test deque implementatioln

#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Deque *deque = deque_new();
    
    for(int i = 0; i < 10; i++) {
        deque_push_back(deque, i);
    }

    deque_print(deque);

    
    deque_push_front(deque, 10);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    //deque_pop_back(deque);
    deque_print(deque);
    printf("size: %d\n", deque_size(deque));

    deque_delete(deque);
    return 0;
}