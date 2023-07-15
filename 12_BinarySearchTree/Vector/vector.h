#ifndef VECTOR_H
#define VECTOR_H
#define INITIAL_CAPACITY 10

/**
 * @brief Vector data structure.
 */
typedef struct Vector Vector;

/**
 * @brief Constructs a new vector.
 * 
 * @return Pointer to the newly created vector.
 * 
 * @note Complexity: O(1)
 */
Vector *vector_construct();

/**
 * @brief Destroys the vector and frees the associated memory.
 * 
 * @param v Pointer to the vector to be destroyed.
 * 
 * @note Complexity: O(n)
 */
void vector_destroy(Vector *v);

/**
 * @brief Adds an element to the end of the vector.
 * 
 * @param v Pointer to the vector.
 * @param val Pointer to the value to be added.
 * 
 * @note Complexity: O(1) amortized
 */
void vector_push_back(Vector *v, void* val);

/**
 * @brief Returns the number of elements in the vector.
 * 
 * @param v Vector to be checked.
 * @return int Size of the vector.
 * 
 * @note Complexity: O(1)
 */
int vector_size(Vector *v);

/**
 * @brief Returns the element at the specified index in the vector.
 * 
 * @param v Pointer to the vector.
 * @param i Index of the element to retrieve.
 * @return void* Pointer to the element.
 * 
 * @note Complexity: O(1)
 */
void* vector_get(Vector *v, int i);

/**
 * @brief Sets the value of the element at the specified index in the vector.
 * 
 * @param v Pointer to the vector.
 * @param i Index of the element to set.
 * @param val Pointer to the value to be set.
 * 
 * @note Complexity: O(1)
 */
void vector_set(Vector *v, int i, void* val);

/**
 * @brief Finds the first occurrence of the specified value in the vector.
 * 
 * @param v Pointer to the vector.
 * @param val Pointer to the value to be found.
 * @return int Index of the first occurrence of the value, or -1 if not found.
 * 
 * @note Complexity: O(n)
 */
int vector_find(Vector *v, void* val);

/**
 * @brief Removes the element at the specified index from the vector.
 * 
 * @param v Pointer to the vector.
 * @param i Index of the element to remove.
 * @return void* Pointer to the removed element.
 * 
 * @note Complexity: O(n)
 */
void* vector_remove(Vector *v, int i);

/**
 * @brief Removes and returns the element at the front of the vector.
 * 
 * @param v Pointer to the vector.
 * @return void* Pointer to the removed element.
 * 
 * @note Complexity: O(n)
 */
void* vector_pop_front(Vector *v);

/**
 * @brief Removes and returns the element at the end of the vector.
 * 
 * @param v Pointer to the vector.
 * @return void* Pointer to the removed element.
 * 
 * @note Complexity: O(1)
 */
void* vector_pop_back(Vector *v);

/**
 * @brief Inserts a value at the specified index in the vector.
 * 
 * @param v Pointer to the vector.
 * @param i Index at which the value should be inserted.
 * @param val Pointer to the value to be inserted.
 * 
 * @note Complexity: O(n)
 */
void vector_insert(Vector *v, int i, void* val);

/**
 * @brief Swaps the positions of two elements in the vector.
 * 
 * @param v Pointer to the vector.
 * @param i Index of the first element.
 * @param j Index of the second element.
 * 
 * @note Complexity: O(1)
 */
void vector_swap(Vector *v, int i, int j);

/**
 * @brief Sorts the elements in the vector in ascending order.
 * 
 * @param v Pointer to the vector.
 * 
 * @note Complexity: O(n^2)
 */
void vector_sort(Vector *v);

/**
 * @brief Sorts the elements in the vector using the bubble sort algorithm.
 * 
 * @param v Pointer to the vector.
 * 
 * @note Complexity: O(n^2)
 */
void vector_bubble_sort(Vector *v);

/**
 * @brief Performs a binary search on the vector to find the specified value.
 * 
 * @param v Pointer to the vector.
 * @param val Pointer to the value to be searched.
 * @return int Index of the found value, or -1 if not found.
 * 
 * @note Complexity: O(log n)
 */
int vector_binary_search(Vector *v, void* val);

/**
 * @brief Reverses the order of elements in the vector.
 * 
 * @param v Pointer to the vector.
 * 
 * @note Complexity: O(n)
 */
void vector_reverse(Vector *v);

/**
 * @brief Creates a copy of the vector.
 * 
 * @param v Pointer to the vector to be copied.
 * @return Pointer to the newly created copy of the vector.
 * 
 * @note Complexity: O(n)
 */
Vector *vector_copy(Vector *v);

/**
 * @brief Removes all elements from the vector.
 * 
 * @param v Pointer to the vector.
 * 
 * @note Complexity: O(1)
 */
void vector_clear(Vector *v);

/**
 * @brief Finds all occurrences of the specified value in the vector and returns their indices.
 * 
 * @param v Pointer to the vector.
 * @param val Pointer to the value to be found.
 * @return int* Array of indices of the occurrences.
 * 
 * @note Complexity: O(n)
 */
int* vector_find_all(Vector *v, void* val);

/**
 * @brief Prints the elements of the vector using the specified print function.
 * 
 * @param v Pointer to the vector.
 * @param printfn Function pointer to the print function.
 * 
 * @note Complexity: O(n)
 */
void vector_print(Vector *v, void (*printfn)(void*));

#endif 
