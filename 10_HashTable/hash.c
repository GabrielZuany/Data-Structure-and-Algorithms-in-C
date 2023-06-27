
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"
#include "../03_Forward_List/forward_list.h"
#include "../03_Forward_List/node.h"

struct HashTable{
    int size;
    hash_function hash_func;
    cmp_hash_values cmp_func;
    ForwardList **table;
}; 

typedef struct HashTableItem HashTableItem;
struct HashTableItem{
    void *key;
    void *val;
};

typedef struct HashTableIterator HashTableIterator;
struct HashTableIterator{
    HashTable *h;
    int index;
    Node *node;
};

HashTable *hash_table_construct(int size, hash_function hash_func, cmp_hash_values cmp_func){
    HashTable *h = malloc(sizeof(HashTable));
    h->size = size;
    h->hash_func = hash_func;
    h->cmp_func = cmp_func;
    h->table = malloc(sizeof(ForwardList *) * size);
    for(int i = 0; i < size; i++){
        h->table[i] = forward_list_construct();
    }
    return h;
}

int hash_table_size(HashTable *h){
    return h->size;
}

void hash_table_set(HashTable *h, void* key, void *val){
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];

    // go to index and get the first node
    Node *node = forward_list_get_head_node(list);

    // if node == NULL then the list is empty and we can just push the item
    while(node != NULL){
        HashTableItem *item = node_get_value(node);

        // check if the key is already in the list to update the value
        if(h->cmp_func(item->key, key) == 0){
            item->val = val;
            return;
        }

        // if not, go to the next node until we find the key or reach the end of the list
        node = node_get_next(node);
    }

    // pushing a new item to the list
    HashTableItem *item = malloc(sizeof(HashTableItem));
    item->key = key;
    item->val = val;
    forward_list_push_front(list, item);
    return;
}

void *hash_table_get(HashTable *h, void* key){
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];

    // go to index and get the first node
    Node *node = forward_list_get_head_node(list);

    // if node == NULL then the list is empty and we can just push the item
    while(node != NULL){
        HashTableItem *item = node_get_value(node);

        // check if the key is already in the list to update the value
        if(h->cmp_func(item->key, key) == 0){
            return item->val;
        }

        // if not, go to the next node until we find the key or reach the end of the list
        node = node_get_next(node);
    }

    return NULL;
}
/*

void *hash_table_pop(HashTable *h, int key);

void hash_table_destroy(HashTable *h);*/