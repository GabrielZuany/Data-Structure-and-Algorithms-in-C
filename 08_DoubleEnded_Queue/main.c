#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"

int main(){
    Deque *d = deque_new(10);
    for(int i = 0; i < 10; i++){
        deque_push_back(d, i);
    }
    deque_print(d);

    //deque_push_back(d, 100);


    deque_push_front(d, 100);
    deque_push_back(d, 150);

    deque_print(d);


    
    deque_delete(d);
    return 0;
}

