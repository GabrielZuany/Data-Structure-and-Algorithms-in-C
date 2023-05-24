#ifndef _STACK_H_
#define _STACK_H_
#include "../04_Double_Linked_List/list.h"
#include "../04_Double_Linked_List/node.h"

typedef int data_type;
typedef struct Stack Stack;

/**
 * @brief Construct a new Stack object
 * 
 * @return Stack* 
 * 
 * @note Complexity: O(1)
 */
Stack *stack_construct();

/**
 * @brief Pushes the given element value to the top of the stack.
 * 
 * @param s 
 * @param val 
 * 
 * @note This member function effectively calls the member function push_back of the underlying container object.
 * @note Complexity: O(1)
 */
void stack_push(Stack *s, data_type val);

/**
 * @brief Removes the top element from the stack.
 * 
 * @param s 
 * @return data_type 
 * 
 * @note This member function effectively calls the member function pop_back of the underlying container object.
 * @note Complexity: O(1)
 */
data_type stack_pop(Stack *s);

/**
 * @brief Prints the stack.
 * 
 * @param s 
 * @param print_fn 
 * 
 * @note Complexity: O(n)
 */
void stack_print(Stack *s, void (*print_fn)(data_type));

/**
 * @brief Checks if the stack is empty.
 * 
 * @param s 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int stack_empty(Stack *s);

/**
 * @brief Destroy the Stack object
 * 
 * @param s 
 * 
 * @note Complexity: O(n)
 */
void stack_destroy(Stack *s);

#endif