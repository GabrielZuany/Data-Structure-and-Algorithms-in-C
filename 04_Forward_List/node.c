#include "node.h"
#include <stdlib.h>

Node *node_construct(data_type value, Node *next){
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

void node_destroy(Node *n){
    free(n);
}

void node_destroy_Rec(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_Rec(n->next);
    node_destroy(n);
}