#ifndef list_H_
#define list_H_

#include "dll_node.h"

typedef struct List List;

/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return List*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using list_destroy().
 * 
 * @note Complexity: O(1)
 *
 */
List *list_construct();

/**
 * @brief Returns the size of the linked list.
 *  Returns the number of dll_nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of dll_nodes in the linked list.
 * 
 * @note Complexity: O(1)
 *
 */
int list_size(List *l);

/**
 * @brief Returns the data stored in the first dll_node of the linked list.
 * 
 * @param l 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* list_get_first(List *l);

/**
 * @brief Returns the data stored in the last dll_node of the linked list.
 * 
 * @param l 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* list_get_last(List *l);

/**
 * @brief Pushes a new dll_node to the front of the linked list.
 *  Allocates memory for a new dll_node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new dll_node.
 * 
 * @note Complexity: O(1)
 *
 */
void list_push_front(List *l, void* data);


/**
 * @brief Pushes a new dll_node to the back of the linked list.
 *  Allocates memory for a new dll_node and inserts it at the back of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new dll_node.
 * 
 * @note Complexity: O(1)
 *
 */
void list_push_back(List *l, void* data);

/**
 * @brief Get the last dll_node of the linked list.
 * 
 * @param l 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* list_back(List *l);

/**
 * @brief Removes the dll_node at the given index from the linked list.
 *  Removes the dll_node at the given index from the linked list and frees the memory allocated for it.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the dll_node to be removed.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the dll_node.
 * 
 * @note Complexity: O(1)
 *
 */
void* list_pop_back(List *l);

/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print void* values.
 *
 * @note Complexity: O(n)
 */
void list_print(List *l, void (*print_fn)(void*));


/**
 * @brief Print the elements of the linked list in reverse order.
 *  Print the elements of the linked list in reverse order.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print void* values.
 *
 * @note Complexity: O(n)
 */
void list_print_reverse(List *l, void (*print_fn)(void*));

/**
 * @brief Returns the data stored in the dll_node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the dll_node.
 * @return void*
 * Data stored in the dll_node at the given index.
 *
 * @note Complexity: O(n)
 */
void* list_get(List *l, int i);

/**
 * @brief Remove the first dll_node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return void*
 * Pointer to the data stored in the first dll_node of the linked list that was removed.
 *
 * @note Complexity: O(1)
 */
void* list_pop_front(List *l);

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return List*
 * Pointer to the newly allocated linked list.
 * 
 * @note Complexity: O(n)
 */
List *list_reverse(List *l);


/**
 * @brief Removes all dll_nodes with the given value from the linked list.
 * Removes all dll_nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 * 
 * @note Complexity: O(n)
 */
void list_remove(List *l, void* val);

/**
 * @brief Adds all dll_nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 * 
 * @note Complexity: O(n)
 */
void list_cat(List *l, List *m);

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its dll_nodes.
 * @param l
 * Pointer to the linked list.
 *
 * @note Complexity: O(n)
 */
void list_destroy(List *l);

#endif