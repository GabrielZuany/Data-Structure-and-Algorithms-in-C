#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "binary_tree.h"

int cmp_int(void* a, void*b){
    return *(int*)a - *(int*)b;
}

void key_printer(void* key){
    printf("%d", *(int*)key);
}

void val_printer(void* val){
    printf("%d", *(int*)val);
}


int main(){

    BinaryTree* bt = binary_tree_construct(cmp_int, NULL, NULL);

    KeyValPair* kv1 = key_val_pair_construct((void*)1, (void*)10);
    KeyValPair* kv2 = key_val_pair_construct((void*)2, (void*)20);


    binary_tree_add(bt, key_val_pair_get_key(kv1), key_val_pair_get_val(kv1));
    binary_tree_add(bt, key_val_pair_get_key(kv2), key_val_pair_get_val(kv2));

    return 0;
}