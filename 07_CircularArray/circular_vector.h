#ifndef _CIRCULAR_VECTOR_H_
#define _CIRCULAR_VECTOR_H_
#define DEFAULT_CAPACITY 5
#define EMPTY -999
#define null -1

typedef struct CircularVector CircularVector;

typedef int Bool;
#define true 1
#define false 0

/**
 * @brief Set the current vector to default config (dealloc part of memory and reset to DEFAULT_CAPACITY)
 * 
 * @param cv 
 * 
 * @note Complexity O(n)
 */
void circular_vector_default(CircularVector* cv);

/**
 * @brief clear the Circular Vector object (set all values to 0)
 * 
 * @param cv 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_clear(CircularVector* cv);

/**
 * @brief create a new Circular Vector object (static by default)
 * 
 * @param define_total_capacity 
 * @return CircularVector* 
 * 
 * @note Complexity: O(1)
 */
CircularVector *circular_vector_new(int define_total_capacity);

/**
 * @brief create a new Circular Vector object (dynamic)
 * 
 * @param define_total_capacity 
 * @return CircularVector* 
 * 
 * @note Complexity: O(1)
 */
CircularVector *dynamic_circular_vector_new(int define_total_capacity);

/**
 * @brief create a new Circular Vector object (static)
 * 
 * @param define_total_capacity 
 * @return CircularVector* 
 * 
 * @note Complexity: O(1)
 */
CircularVector *static_circular_vector_new(int define_total_capacity);

/**
 * @brief reallocate the memory for the Circular Vector object
 * 
 * @param cv 
 * @return void* 
 * 
 * @note Complexity: O(n)
 */
void *circular_vector_realloc(CircularVector *cv);

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
void circular_vector_push_back(CircularVector *cv, void* value);

/**
 * @brief insert a new value at the start of the Circular Vector object
 * 
 * @param cv 
 * @param value 
 * 
 * @note Complexity: O(1)
 */
void circular_vector_push_front(CircularVector *cv, void* value);

/**
 * @brief remove the value at the index position of the Circular Vector object
 * 
 * @param cv 
 * @param index 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_pop_index(CircularVector *cv, int index);

/**
 * @brief insert a new value at the index position of the Circular Vector object
 * 
 * @param cv 
 * @param index 
 * @param value 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_fix_end_ptr(CircularVector *cv); 

/**
 * @brief insert a new value at the index position of the Circular Vector object
 * 
 * @param cv 
 * @param index 
 * @param value 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_fix_init_ptr(CircularVector *cv); 

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
void* circular_vector_get(CircularVector *cv, int index);

/**
 * @brief print the Circular Vector object
 * 
 * @param cv 
 * 
 * @note Complexity: O(n)
 */
void circular_vector_print(CircularVector *cv, void(*printfn)(void*));
#endif