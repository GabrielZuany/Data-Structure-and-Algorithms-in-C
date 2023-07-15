#include "dll_node.h"
#include <stdlib.h>

struct dll_node
{
    void** value;
    struct dll_node *next;
    struct dll_node *prev;
};

dll_node *dll_node_construct(void* value, dll_node *next, dll_node *prev){
    dll_node *dll_node = (struct dll_node *)malloc(sizeof(struct dll_node));
    dll_node->value = value;
    dll_node->next = next;
    dll_node->prev = prev;
    return dll_node;
}

void* dll_node_get_data(dll_node *n){
    return n->value;
}

dll_node *dll_node_get_next(dll_node *n){
    return n->next;
}

dll_node *dll_node_get_prev(dll_node *n){
    return n->prev;
}

void dll_node_set_data(dll_node *n, void* value){
    n->value = value;
}

void dll_node_set_next(dll_node *n, dll_node *next){
    n->next = next;
}

void dll_node_set_prev(dll_node *n, dll_node *prev){
    n->prev = prev;
}

void dll_node_destroy(dll_node *n){
    free(n);
}

void dll_node_destroy_recursive(dll_node* n){
    if (n==NULL){
        return;
    }
    if(n->next != NULL)
        dll_node_destroy_recursive(n->next);
    dll_node_destroy(n);
}