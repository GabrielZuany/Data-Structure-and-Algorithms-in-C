#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct Stack{
    List *list;
};

Stack *stack_construct(){
    Stack* s = malloc(sizeof(Stack));
    s->list = list_construct();
    return s;
}

void stack_push(Stack *s, void* val){
    list_push_back(s->list, val);
}

void* stack_pop(Stack *s){
    return list_pop_back(s->list);
}

void* stack_top(Stack *s){
    return list_back(s->list);
}

void stack_print(Stack *s, void (*print_fn)(void*)){
    list_print(s->list, print_fn);
}

int stack_empty(Stack *s){
    if(list_size(s->list) == 0){
        return 1;
    } return 0;
}

void stack_destroy(Stack *s){
    for(int i = 0; i < list_size(s->list); i++){
        free(list_pop_back(s->list));
    }
    free(s->list);
    free(s);
}