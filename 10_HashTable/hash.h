#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef struct HashTable HashTable;
typedef int (*hash_function)(HashTable* h, void* key);
typedef int (*cmp_hash_values)(void* key1, void* key2);
HashTable *hash_table_construct(int size, hash_function hash_function, cmp_hash_values cmp_function);

void hash_table_set(HashTable *h, void* key, void *val);

void *hash_table_get(HashTable *h, void* key);

void *hash_table_pop(HashTable *h, void* key);

int hash_table_size(HashTable *h);

void hash_table_destroy(HashTable *h);




typedef struct HashTableItem HashTableItem;
void* hash_table_item_get_key(HashTableItem *item);

void* hash_table_item_get_value(HashTableItem *item);



typedef struct HashTableIterator HashTableIterator;
HashTableIterator *hash_table_iterator_construct(HashTable *h);

int hash_table_iterator_is_over(HashTableIterator *it);

int hash_table_iterator_has_next(HashTableIterator *it);

HashTableItem *hash_table_iterator_next(HashTableIterator *it);

void hash_table_iterator_destroy(HashTableIterator *it);

#endif