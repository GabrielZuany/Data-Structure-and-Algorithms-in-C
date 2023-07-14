#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "vector.h"

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);
typedef struct Node Node;
typedef struct BinaryTree BinaryTree;
typedef struct KeyValPair KeyValPair;
void binary_tree_print(BinaryTree* bt, void (*key_printer)(void*), void (*val_printer)(void*));

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kv, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);
void *key_val_pair_get_key(KeyValPair *kvp);
void *key_val_pair_get_val(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right, Node* parent);
void node_destroy(Node *node);

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn);

void binary_tree_add(BinaryTree *bt, void *key, void *value);

int binary_tree_empty(BinaryTree *bt);

KeyValPair* binary_tree_min(BinaryTree *bt);

KeyValPair* binary_tree_max(BinaryTree *bt);

void *binary_tree_get(BinaryTree *bt, void *key);
KeyValPair* binary_tree_pop_min(BinaryTree *bt);
KeyValPair* binary_tree_pop_max(BinaryTree *bt);
void binary_tree_delete(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);
Vector* inorder_recursive(Node* root, Vector* vec);
Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);
/*

Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);*/

#endif