#ifndef _STACK_H_
#define _STACK_H_
#include "../List/list.h"
#include "../List/dll_node.h"

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
void stack_push(Stack *s, void* val);

/**
 * @brief Removes the top element from the stack.
 * 
 * @param s 
 * @return void* 
 * 
 * @note This member function effectively calls the member function pop_back of the underlying container object.
 * @note Complexity: O(1)
 */
void* stack_pop(Stack *s);

/**
 * @brief Returns a reference to the top element in the stack.
 * 
 * @param s 
 * @return void* 
 * 
 * @note This member function effectively calls the member function back of the underlying container object.
 * @note Complexity: O(1)
 */
void* stack_top(Stack *s);

/**
 * @brief Prints the stack.
 * 
 * @param s 
 * @param print_fn 
 * 
 * @note Complexity: O(n)
 */
void stack_print(Stack *s, void (*print_fn)(void*));

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