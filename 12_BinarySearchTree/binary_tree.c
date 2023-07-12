#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct KeyValPair
{
    void *key;
    void *value;
};

struct Node
{
    void *key;
    void *value;
    struct Node *left;
    struct Node *right;
};

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

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

void *key_val_pair_get_key(KeyValPair *kvp){
    return kvp->key;
}

void *key_val_pair_get_val(KeyValPair *kvp){
    return kvp->value;
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
    if(bt->root == NULL){
        bt->root = node_construct(key, value, NULL, NULL);
        return;
    }

    Node* new = node_construct(key, value, NULL, NULL);
    Node* root = bt->root;
    Node* left = root->left;
    Node* right = root->right;

    while(1){
        if(bt->cmp_fn(key, root->key) == 0){
            bt->key_destroy_fn(root->key);
            bt->val_destroy_fn(root->value);
            root->key = key;
            root->value = value;
            node_destroy(new);
            return;
        }
        if(bt->cmp_fn(key, root->key) < 0){
            if(left == NULL){
                root->left = new;
                return;
            }
            root = left;
            left = root->left;
            right = root->right;
        }
        else{
            if(right == NULL){
                root->right = new;
                return;
            }
            root = right;
            left = root->left;
            right = root->right;
        }
    }
}

void print_root_left_and_right(Node* root, void (*key_printer)(void*), void (*val_printer)(void*)){
    printf("root: ");
    if(root == NULL){
        printf("NULL\n");
        return;
    }else{
        key_printer(root->key);
        printf(" ");
        val_printer(root->value);
        printf("\n");
    }
    printf("left: ");
    if(root->left == NULL){
        printf("NULL\n");
    }
    else{
        key_printer(root->left->key);
        printf(" ");
        val_printer(root->left->value);
        printf("\n");
    }

    printf("right: ");
    if(root->right == NULL){
        printf("NULL\n");
    }
    else{
        key_printer(root->right->key);
        printf(" ");
        val_printer(root->right->value);
        printf("\n");
    }

    printf("\n");

    if(root->left != NULL){
        print_root_left_and_right(root->left, key_printer, val_printer);
    }
    if(root->right != NULL){
        print_root_left_and_right(root->right, key_printer, val_printer);
    }
}

void binary_tree_print(BinaryTree* bt, void (*key_printer)(void*), void (*val_printer)(void*)){
    print_root_left_and_right(bt->root, key_printer, val_printer);
}

int binary_tree_empty(BinaryTree *bt){
    if(bt->root == NULL){
        return 1;
    }
    return 0;
}

KeyValPair* binary_tree_max(BinaryTree *bt){
    Node* root = bt->root;
    while(root->right != NULL){
        root = root->right;
    }
    return key_val_pair_construct(root->key, root->value);
}

KeyValPair* binary_tree_min(BinaryTree *bt){
    Node* root = bt->root;
    while(root->left != NULL){
        root = root->left;
    }
    return key_val_pair_construct(root->key, root->value);
}

void *binary_tree_get(BinaryTree *bt, void *key){
    Node* root = bt->root;
    while( root != NULL ){
        if(root == NULL){
            return NULL;
        }
        if(bt->cmp_fn(key, root->key) < 0 ){
            root = root->left;
            continue;
        }
        if(bt->cmp_fn(key, root->key) > 0 ){
            root = root->right;
            continue;
        }
        return root->value;
    }
}

KeyValPair* binary_tree_pop_min(BinaryTree *bt){
    Node* root = bt->root;
    Node* parent = NULL;
    while(root->left != NULL){
        parent = root;
        root = root->left;
    }
    KeyValPair* new = key_val_pair_construct(root->key, root->value);
    node_destroy(root);
    parent->left = NULL;
    return new;
}

KeyValPair* binary_tree_pop_max(BinaryTree *bt){
    Node* root = bt->root;
    Node* parent = NULL;
    while(root->right != NULL){
        parent = root;
        root = root->right;
    }
    KeyValPair* new = key_val_pair_construct(root->key, root->value);
    node_destroy(root);
    parent->right = NULL;
    return new;
}

void binary_tree_destroy(BinaryTree *bt){
    
}
/*
void binary_tree_remove(BinaryTree *bt, void *key);



Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
*/