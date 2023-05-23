#ifndef _NODE_H_
#define _NODE_H_

typedef int data_type;

typedef struct Node Node;

/**
 * @brief Construct a new Node
 * 
 * @param value 
 * @param next 
 * @param prev 
 * @return Node* 
 * 
 * @note Complexity: O(1)
 */
Node *node_construct(data_type value, Node *next, Node* prev);

/**
 * @brief Get the data object
 * 
 * @param n 
 * @return data_type 
 * 
 * @note Complexity: O(1)
 */
data_type node_get_data(Node *n);

/**
 * @brief Get the next object
 * 
 * @param n 
 * @return Node* 
 * 
 * @note Complexity: O(1)
 */
Node *node_get_next(Node *n);

/**
 * @brief Get the prev object
 * 
 * @param n 
 * @return Node* 
 * 
 * @note Complexity: O(1)
 */
Node *node_get_prev(Node *n);

/**
 * @brief Set the data object
 * 
 * @param n 
 * @param value 
 * 
 * @note Complexity: O(1)
 */
void node_set_data(Node *n, data_type value);

/**
 * @brief Set the next object
 * 
 * @param n 
 * @param next 
 * 
 * @note Complexity: O(1)
 */
void node_set_next(Node *n, Node *next);

/**
 * @brief Set the prev object
 * 
 * @param n 
 * @param prev 
 * 
 * @note Complexity: O(1)
 */
void node_set_prev(Node *n, Node *prev);

/**
 * @brief Destroy the Node object
 * 
 * @param n 
 * 
 * @note Complexity: O(1)
 */
void node_destroy(Node *n);

/**
 * @brief Destroy the Node object recusive
 * 
 * @param n 
 * 
 * @note Complexity: O(n)
 */
void node_destroy_recursive(Node* n);

#endif