#include "node.h"
#include <stdlib.h>

struct Node
{
    data_type value;
    struct Node *next;
    struct Node *prev;
};

Node *node_construct(data_type value, Node *next, Node *prev){
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    node->prev = prev;
    return node;
}

data_type node_get_data(Node *n){
    return n->value;
}

Node *node_get_next(Node *n){
    return n->next;
}

Node *node_get_prev(Node *n){
    return n->prev;
}

void node_set_data(Node *n, data_type value){
    n->value = value;
}

void node_set_next(Node *n, Node *next){
    n->next = next;
}

void node_set_prev(Node *n, Node *prev){
    n->prev = prev;
}

void node_destroy(Node *n){
    free(n);
}

void node_destroy_recursive(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_recursive(n->next);
    node_destroy(n);
}