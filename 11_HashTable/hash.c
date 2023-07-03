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

void* hash_table_set(HashTable *h, void* key, void *val){
    static int count = 0;
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];

    Node *node = forward_list_get_head_node(list);

    while(node != NULL){
        HashTableItem *item = node_get_value(node);
        if(h->cmp_func(item->key, key) == 0){
            free(item->val);
            item->val = val;
            return item;
        }
        node = node_get_next(node);
    }
    
    HashTableItem *item = malloc(sizeof(HashTableItem));
    item->key = key;
    item->val = val;
    forward_list_push_front(list, item);
        
    return NULL;
}

void *hash_table_get(HashTable *h, void* key){
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];
    Node *node = forward_list_get_head_node(list);

    while(node != NULL){
        HashTableItem *item = node_get_value(node);
        if(h->cmp_func(item->key, key) == 0){
            return item->val;
        }
        node = node_get_next(node);
    }

    return NULL;
}

void *hash_table_pop(HashTable *h, void* key){
    void *val = NULL;
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];

    Node *node = forward_list_get_head_node(list);

    while(node != NULL){
        HashTableItem *item = node_get_value(node);
        if(h->cmp_func(item->key, key) == 0){
            val = item->val;
            forward_list_remove_node(list, node);
            free(item);
            break;
        }
        node = node_get_next(node);
    }

    return val;
}

void hash_table_destroy(HashTable* h, void (*key_destructor)(void*, ...), void (*val_destructor)(void*, ...)){
    int i = 0;
    for(i = 0; i<h->size ; i++){
        ForwardList *list = h->table[i];
        Node *node = forward_list_get_head_node(list);
        while(node != NULL){
            HashTableItem *item = node_get_value(node);
            if(key_destructor != NULL){
                key_destructor(item->key);
            }
            if(val_destructor != NULL){
                val_destructor(item->val);
            }
            free(item);
            node = node_get_next(node);
        }
        forward_list_destroy(h->table[i]);
    }
    free(h->table);
    free(h);
}