#ifndef _ED_VECTOR_H_
#define _ED_VECTOR_H_
#define INITIAL_CAPACITY 10
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

/**
 * @brief Set the i-th element of the vector.
 * 
 * @param v vector to be modified.
 * @param i index of the element.
 * @param val value to be set.
 * 
 * @note Complexity: O(1)
 */
void vector_set(Vector *v, int i, data_type val);

/**
 * @brief Returns the index of the first occurrence of val in the vector.
 * 
 * @param v vector to be checked.
 * @param val value to be found.
 * @return int value of the index.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
int vector_find(Vector *v, data_type val);

/**
 * @brief Remove the i-th element of the vector.
 * 
 * @param v vector to be modified.
 * @param i index of the element.
 * @return data_type value of the removed element.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
data_type vector_remove(Vector *v, int i); 

/**
 * @brief Remove the first occurrence of val in the vector.
 * 
 * @param v vector to be modified.
 * @return data_type value of the removed element.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
data_type vector_pop_front(Vector *v); 

/**
 * @brief Remove the last element of the vector.
 * 
 * @param v vector to be modified.
 * @return data_type value of the removed element.
 * 
 * @note Complexity: O(1)
 */
data_type vector_pop_back(Vector *v); 

/**
 * @brief Insert val at the beginning of the vector.
 * 
 * @param v vector to be modified.
 * @param i index of the element.
 * @param val value to be inserted.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
void vector_insert(Vector *v, int i, data_type val); 

/**
 * @brief Insert val at the end of the vector.
 * 
 * @param v vector to be modified.
 * @param i index of 1st element.
 * @param j index of 2nd element.
 * 
 * @note Complexity: O(1)
 */
void vector_swap(Vector *v, int i, int j); 

/**
 * @brief Sort the vector.
 * 
 * @param v vector to be sorted.
 * 
 * @note Complexity: O(n^2) => depends on the size of the vector.
 * @note Uses a different implementation of bubble sort.
 */
void vector_sort(Vector *v);

/**
 * @brief Sort the vector using bubble sort.
 * 
 * @param v vector to be sorted.
 * 
 * @note Complexity: O(n^2) => depends on the size of the vector.
 */
void vector_bubble_sort(Vector *v);

/**
 * @brief Binary search for val in the vector.
 * 
 * @param v vector to be searched.
 * @param val value to be found.
 * @return int index of the element.
 * 
 * @note Complexity: O(log n) => depends on the size of the vector.
 */
int vector_binary_search(Vector *v, data_type val);

/**
 * @brief Reverse the vector.
 * 
 * @param v vector to be reversed.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
void vector_reverse(Vector *v); 

/**
 * @brief Copy the vector.
 * 
 * @param v vector to be copied.
 * @return Vector* 
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 * @note Uses memcpy.
 */
Vector *vector_copy(Vector *v); 

/**
 * @brief Clear the vector.
 * 
 * @param v vector to be cleared.
 * 
 * @note Complexity: O(1)
 */
void vector_clear(Vector *v);

/**
 * @brief Find all occurrences of val in the vector
 * 
 * @param v vector to be searched.
 * @param val value to be found.
 * @return int* array of indexes.
 * 
 * @note Complexity: O(n) => depends on the size of the vector.
 */
int* vector_find_all(Vector *v, data_type val);

#endif