#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include <stdarg.h>

typedef struct HashTable HashTable;
typedef int (*hash_function)(HashTable* h, void* key);
typedef int (*cmp_hash_values)(void* key1, void* key2);

typedef struct HashTableItem{
    void *key;
    void *val;
}HashTableItem;

void hash_table_destroy(HashTable* h, void (*key_destructor)(void*, ...), void (*val_destructor)(void*, ...));

HashTable *hash_table_construct(int size, hash_function hash_function, cmp_hash_values cmp_function);

void* hash_table_set(HashTable *h, void* key, void* val);

void *hash_table_get(HashTable *h, void* key);

void *hash_table_pop(HashTable *h, void* key);

int hash_table_size(HashTable *h);


#endif