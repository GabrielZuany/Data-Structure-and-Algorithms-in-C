#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void *key;
    void *value;
} KeyValPair;

typedef struct Node
{
    void *key;
    void *value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
} BinaryTree;

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair* new = malloc(sizeof(KeyValPair));
    new->key = key;
    new->value = val;
    return new;
}

void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    if(key_destroy_fn != NULL){
        key_destroy_fn(kvp->key);
    }
    if(val_destroy_fn != NULL){
        val_destroy_fn(kvp->value);
    }
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node* new = malloc(sizeof(Node));
    new->key = key;
    new->value = value;
    new->left = left;
    new->right = right;
    return new;
}
void node_destroy(Node *node){
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree* new = malloc(sizeof(BinaryTree));
    new->root = NULL;
    new->cmp_fn = cmp_fn;
    new->key_destroy_fn = key_destroy_fn;
    new->val_destroy_fn = val_destroy_fn;
    return new;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    Node* new = node_construct(key, value, NULL, NULL);
    Node* child = bt->root;

    while(child != NULL){
        if(bt->cmp_fn(new->key, child->right->key) > 0){
            child = child->right;
            continue;
        }
        else if(bt->cmp_fn(new->key, child->left->key) < 0){
            child = child->left;
            continue;
        }
        else{
            child = child->right;
            continue;
        }
    }
    child = new;
    child->left = NULL;
    child->right = NULL;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair binary_tree_min(BinaryTree *bt);
KeyValPair binary_tree_max(BinaryTree *bt);
KeyValPair binary_tree_pop_min(BinaryTree *bt);
KeyValPair binary_tree_pop_max(BinaryTree *bt);
void *binary_tree_get(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
