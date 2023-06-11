#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "node.h"

/**
 * @file deque.h
 * @brief Double-Ended Queue (Deque) Data Structure
 */

/**
 * @brief Deque structure
 */
typedef struct Deque {
    Node* front; /**< Pointer to the front node of the deque */
    Node* rear; /**< Pointer to the rear node of the deque */
} Deque;

/**
 * @brief Create an empty deque
 *
 * @return Pointer to the newly created deque
 *
 * @note Complexity: O(1)
 */
Deque* deque_create();

/**
 * @brief Check if the deque is empty
 *
 * @param deque Pointer to the deque
 * @return 1 if the deque is empty, 0 otherwise
 *
 * @note Complexity: O(1)
 */
int deque_empty(Deque* deque);

/**
 * @brief Insert an element at the front of the deque
 *
 * @param deque Pointer to the deque
 * @param data Pointer to the data to be inserted
 *
 * @note Complexity: O(1)
 */
void deque_push_front(Deque* deque, void* data);

/**
 * @brief Insert an element at the rear of the deque
 *
 * @param deque Pointer to the deque
 * @param data Pointer to the data to be inserted
 *
 * @note Complexity: O(1)
 */
void deque_push_back(Deque* deque, void* data);

/**
 * @brief Delete an element from the front of the deque
 *
 * @param deque Pointer to the deque
 *
 * @note Complexity: O(1)
 */
void deque_pop_front(Deque* deque);

/**
 * @brief Delete an element from the rear of the deque
 *
 * @param deque Pointer to the deque
 *
 * @note Complexity: O(1)
 */
void deque_pop_back(Deque* deque);

/**
 * @brief Display the elements in the deque
 *
 * @param deque Pointer to the deque
 * @param printData Function pointer to print the data stored in each node
 *
 * @note Complexity: O(n)
 */
void deque_print(Deque* deque, void (*printData)(void*));

/**
 * @brief Free memory occupied by the deque
 *
 * @param deque Pointer to the deque
 *
 * @note Complexity: O(n)
 */
void freeDeque(Deque* deque);

#endif
