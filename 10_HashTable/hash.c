#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"
#include "../03_Forward_List/forward_list.h"
#include "../03_Forward_List/node.h"



// ************* HASH TABLE ITEM ************* //

struct HashTableItem{
    void *key;
    void *val;
};

void* hash_table_item_get_key(HashTableItem *item){
    if(item == NULL)
        return NULL;
    return item->key;
}

void* hash_table_item_get_value(HashTableItem *item){
    if (item == NULL)
        return NULL;
    
    return item->val;
}

void hash_table_item_destroy(HashTableItem *item, void (*key_destroy)(void *), void (*val_destroy)(void *)){
    if(item == NULL)
        return;
    
    if(key_destroy != NULL)
        key_destroy(item->key);
    
    if(val_destroy != NULL)
        val_destroy(item->val);

    free(item);        
}




// ************* HASH TABLE ************* //

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

void* hash_table_set(HashTable *h, void* key, void *val, void (*val_destroy)(void *)){
    int hash = h->hash_func(h, key);
    ForwardList *list = h->table[hash];

    // go to index and get the first node
    Node *node = forward_list_get_head_node(list);

    // if node == NULL then the list is empty and we can just push the item
    while(node != NULL){
        HashTableItem *item = node_get_value(node);

        // check if the key is already in the list to update the value
        if(h->cmp_func(item->key, key) == 0){

            if(val_destroy != NULL)
                val_destroy(item->val);

            item->val = val;
            return (void *)item->val;
        }

        // if not, go to the next node until we find the key or reach the end of the list
        node = node_get_next(node);
    }

    // pushing a new item to the list
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
        }
        node = node_get_next(node);
    }

    return val;
}

void hash_table_destroy(HashTable *h){
    int i = 0;
    for(i = 0; i<h->size ; i++){
        forward_list_destroy(h->table[i]);
    }
    free(h->table);
    free(h);
}


// ************* HASH TABLE ITERATOR ************* //
struct HashTableIterator {
    HashTable *h;
    int index;
    Node *node;
};

HashTableIterator *hash_table_iterator_construct(HashTable *h) {
    HashTableIterator *it = malloc(sizeof(HashTableIterator));
    it->h = h;
    it->index = 0;
    it->node = NULL;
    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it) {
    return it->index >= it->h->size;
}

int hash_table_iterator_has_next(HashTableIterator *it) {
    while (it->index < it->h->size && it->node == NULL) {
        it->index++;
        if (it->index < it->h->size) {
            it->node = forward_list_get_head_node(it->h->table[it->index]);
        }
    }
    return it->node != NULL;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if (!hash_table_iterator_has_next(it)) {
        return NULL;
    }

    HashTableItem *item = node_get_value(it->node);
    it->node = node_get_next(it->node);
    return item;
}

void hash_table_iterator_destroy(HashTableIterator *it) {
    free(it);
}