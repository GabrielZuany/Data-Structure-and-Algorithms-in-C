#include "stack.h"
#include "forward_list.h"
#include <stdlib.h>
#include <stdio.h>

struct Stack{
    ForwardList *list;
};

Stack *stack_construct(){
    Stack* s = malloc(sizeof(Stack));
    s->list = forward_list_construct();
    return s;
}

void stack_push(Stack *s, data_type val){
    forward_list_push_front(s->list, val);
}

data_type stack_pop(Stack *s){
    return forward_list_pop_front(s->list); 
}

int stack_empty(Stack *s){
    if(s->list->size == 0){
        return 1;
    } return 0;
}

void stack_destroy(Stack *s){
    forward_list_destroy(s->list);
    free(s);
}