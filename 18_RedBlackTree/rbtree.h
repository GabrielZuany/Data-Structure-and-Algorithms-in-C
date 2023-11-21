#ifndef _RBTREE_H_
#define _RBTREE_H_

#define RED true
#define BLACK false
#include <stdbool.h>

typedef struct node RBT;
typedef void *Key;
typedef void *Value;
typedef int (*compare_t)(Key, Key);

/**
 * @brief Create a RBT object
 * 
 * @param compare_func function to compare the keys
 * @return RBT* 
 * 
 * @note Complexity: O(1)
 */
RBT *RBinit(compare_t compare_func);

/**
 * @brief Insert a new node into the tree
 * 
 * @param h the root of the tree (the tree itself)
 * @param key key of the new node
 * @param val value of the new node
 * @return RBT* 
 * 
 * @note Complexity: O(logN)
 */
RBT *RBT_insert(RBT *h, Key key, Value val);

/**
 * @brief Search for a node with the given key
 * 
 * @param n the root of the tree (the tree itself)
 * @param key key of the node to search
 * @return Value 
 * 
 * @note Complexity: O(logN)
 */
Value search(RBT *n, Key key);

/**
 * @brief Return if the node is red (true) or black (false)
 * 
 * @param x 
 * @return true 
 * @return false 
 * 
 * @note Complexity: O(1)
 */
bool is_red(RBT *x);

/**
 * @brief Rotate the node to the left (fix the 2-3 pseudonode)
 * 
 * @param h 
 * @return RBT* 
 * 
 * @note Complexity: O(1)
 */
RBT *rotate_left(RBT *h);

/**
 * @brief Rotate the node to the right (fix the 2-3 pseudonode)
 * 
 * @param h 
 * @return RBT* 
 * 
 * @note Complexity: O(1)
 */
RBT *rotate_right(RBT *h);

/**
 * @brief if both children are red, flip the colors and pass the red to the parent
 * 
 * @param h 
 * 
 * @note Complexity: O(1)
 */
void flip_colors(RBT *h);


#endif