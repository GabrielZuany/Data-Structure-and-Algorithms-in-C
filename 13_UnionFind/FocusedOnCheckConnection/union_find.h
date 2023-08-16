#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include<stdbool.h>

typedef struct UnionFind UnionFind;

/**
 * @brief Create a Union Find object
 * 
 * @param n number of elements
 * @return UnionFind* 
 * 
 * @note Complexity: O(n)
 */
UnionFind* init(int n);

/**
 * @brief Destroy the Union Find object
 * 
 * @param uf 
 * 
 * @note Complexity: O(1)
 */
void destroy(UnionFind* uf);

/**
 * @brief Check if two elements are connected
 * 
 * @param uf 
 * @param p 
 * @param q 
 * @return true 
 * @return false 
 * 
 * @note Complexity: O(1)
 */
bool isConnected(UnionFind* uf, int p, int q);

/**
 * @brief Find the root of an element
 * 
 * @param uf 
 * @param p 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int find(UnionFind* uf, int p);

/**
 * @brief Connect two elements
 * 
 * @param uf 
 * @param p 
 * @param q 
 * 
 * @note Complexity: O(n) --> 2n+2
 */
void connect(UnionFind* uf, int p, int q);

#endif