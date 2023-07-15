#ifndef _dll_node_H_
#define _dll_node_H_

typedef struct dll_node dll_node;

/**
 * @brief Construct a new dll_node
 * 
 * @param value 
 * @param next 
 * @param prev 
 * @return dll_node* 
 * 
 * @note Complexity: O(1)
 */
dll_node *dll_node_construct(void* value, dll_node *next, dll_node* prev);

/**
 * @brief Get the data object
 * 
 * @param n 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* dll_node_get_data(dll_node *n);

/**
 * @brief Get the next object
 * 
 * @param n 
 * @return dll_node* 
 * 
 * @note Complexity: O(1)
 */
dll_node *dll_node_get_next(dll_node *n);

/**
 * @brief Get the prev object
 * 
 * @param n 
 * @return dll_node* 
 * 
 * @note Complexity: O(1)
 */
dll_node *dll_node_get_prev(dll_node *n);

/**
 * @brief Set the data object
 * 
 * @param n 
 * @param value 
 * 
 * @note Complexity: O(1)
 */
void dll_node_set_data(dll_node *n, void* value);

/**
 * @brief Set the next object
 * 
 * @param n 
 * @param next 
 * 
 * @note Complexity: O(1)
 */
void dll_node_set_next(dll_node *n, dll_node *next);

/**
 * @brief Set the prev object
 * 
 * @param n 
 * @param prev 
 * 
 * @note Complexity: O(1)
 */
void dll_node_set_prev(dll_node *n, dll_node *prev);

/**
 * @brief Destroy the dll_node object
 * 
 * @param n 
 * 
 * @note Complexity: O(1)
 */
void dll_node_destroy(dll_node *n);

/**
 * @brief Destroy the dll_node object recusive
 * 
 * @param n 
 * 
 * @note Complexity: O(n)
 */
void dll_node_destroy_recursive(dll_node* n);

#endif