#ifndef QUEUE_H
#define QUEUE_H

#include "../List/list.h"
#include "../List/dll_node.h"

typedef struct Queue Queue;

/**
 * @brief Create a queue object
 * 
 * @return Queue* 
 * 
 * @note Complexity: O(1)
 */
Queue* create_queue();

/**
 * @brief Returns 1 if the queue is empty, 0 otherwise
 * 
 * @param q 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int queue_empty(Queue* q);

/**
 * @brief Get the size object
 * 
 * @param q 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int queue_size(Queue* q);

/**
 * @brief Get the first value of the queue
 * 
 * @param q 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* queue_front(Queue* q);

/**
 * @brief Get the last value of the queue
 * 
 * @param q 
 * @return void* 
 * 
 * @note Complexity: O(1)
 */
void* queue_back(Queue* q);

/**
 * @brief Push a new value to the back of the queue
 * 
 * @param q 
 * @param data 
 * 
 * @note Complexity: O(1)
 */
void enqueue(Queue* q, void* data);

/**
 * @brief Pop the first value of the queue
 * 
 * @param q 
 * 
 * @note Complexity: O(1)
 */
void* dequeue(Queue* q);

/**
 * @brief Destroy the queue object
 * 
 * @param q 
 * 
 * @note Complexity: O(n)
 */
void queue_destroy(Queue* q);


#endif