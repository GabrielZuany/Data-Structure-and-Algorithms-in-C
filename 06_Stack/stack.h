
#ifndef _STACK_H_
#define _STACK_H_

typedef int data_type;
typedef struct Stack Stack;

Stack *stack_construct();
void stack_push(Stack *s, data_type val);
data_type stack_pop(Stack *s);
int stack_empty(Stack *s);
void stack_destroy(Stack *s);

#endif