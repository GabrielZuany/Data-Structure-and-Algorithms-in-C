#ifndef _ED_VECTOR_H_
#define _ED_VECTOR_H_

typedef int data_type;

typedef struct Vector Vector;

/**
 * @brief Construct a new Vector "object"
 * 
 * @return Vector*
 * 
 * @note Complexity: O(1)
 */
Vector *vector_construct();

/**
 * @brief Destroy the Vector "object".
 * 
 * @param v Vector to be destroyed.
 * 
 * @note Complexity: O(1) 
 */
void vector_destroy(Vector *v);

/**
 * @brief Add a new element to the end of the vector.
 * 
 * @param v Vector to be modified.
 * @param val value to be added.
 * 
 * @note Complexity: O(1) amortized (because of realloc)
 */
void vector_push_back(Vector *v, data_type val);

/**
 * @brief Returns the number of elements in the vector.
 * 
 * @param v Vector to be checked.
 * @return int size of the vector.
 * 
 * @note Complexity: O(1)
 */
int vector_size(Vector *v);

/**
 * @brief Returns the i-th element of the vector.
 * 
 * @param v vector to be checked.
 * @param i index of the element.
 * @return data_type value of the element.
 * 
 * @note Complexity: O(1)
 */
data_type vector_get(Vector *v, int i);

#endif