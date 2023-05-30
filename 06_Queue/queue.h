#ifndef QUEUE_H
#define QUEUE_H

#include "../04_Double_Linked_List/list.h"
#include "../04_Double_Linked_List/node.h"

typedef struct Queue Queue;

/**
 * @brief Create a queue object
 * 
 * @param q 
 * @return int boolean value
 * 
 * @note Complexity: O(1)
 */
int empty(Queue* q);

/**
 * @brief Get the size object
 * 
 * @param q 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int size(Queue* q);

/**
 * @brief Get the first value of the queue
 * 
 * @param q 
 * @return data_type 
 * 
 * @note Complexity: O(1)
 */
data_type front(Queue* q);

/**
 * @brief Get the last value of the queue
 * 
 * @param q 
 * @return data_type 
 * 
 * @note Complexity: O(1)
 */
data_type back(Queue* q);

/**
 * @brief Push a new value to the back of the queue
 * 
 * @param q 
 * @param data 
 * 
 * @note Complexity: O(1)
 */
void push_back(Queue* q, data_type data);

/**
 * @brief Pop the first value of the queue
 * 
 * @param q 
 * 
 * @note Complexity: O(1)
 */
void pop_front(Queue* q);


#endif