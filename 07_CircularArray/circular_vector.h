#ifndef _CIRCULAR_VECTOR_H_
#define _CIRCULAR_VECTOR_H_
#define TOTAL_CAPACITY 10
#define EMPTY -999

typedef struct CircularVector CircularVector;

/**
 * @brief create a new Circular Vector object
 * 
 * @return CircularVector* 
 * 
 * @note Complexity: O(1)
 */
CircularVector *circular_vector_new();

/**
 * @brief free the memory allocated for the Circular Vector object
 * 
 * @param cv 
 * 
 * @note Complexity: O(1)
 */
void circular_vector_free(CircularVector *cv);

/**
 * @brief return the size of the Circular Vector object
 * 
 * @param cv 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int circular_vector_size(CircularVector *cv);

/**
 * @brief insert a new value at the end of the Circular Vector object
 * 
 * @param cv 
 * @param value 
 * 
 * @note Complexity: O(1)
 */
void circular_vector_push_back(CircularVector *cv, int value);

/**
 * @brief remove the start pointer value of the Circular Vector object
 * 
 * @param cv 
 * 
 * @note Complexity: O(1)
 */
void circular_vector_pop_init_ptr(CircularVector *cv);

/**
 * @brief remove the end pointer value of the Circular Vector object
 * 
 * @param cv 
 * 
 * @note Complexity: O(1)
 */
void circular_vector_pop_end_ptr(CircularVector *cv);

/**
 * @brief return the value at the index position of the Circular Vector object
 * 
 * @param cv 
 * @param index 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int circular_vector_get(CircularVector *cv, int index);

/**
 * @brief print the Circular Vector object
 * 
 * @param cv 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_print(CircularVector *cv);

#endif