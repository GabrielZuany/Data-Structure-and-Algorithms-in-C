#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(){
    Deque* d = deque_create();

    for(int i = 0; i<5; i++){
        deque_push_back(d, i + 1);
    }
    
    deque_print(d);

    deque_destroy(d);
    return 0;
}