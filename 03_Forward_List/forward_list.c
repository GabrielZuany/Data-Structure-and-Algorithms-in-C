#include<stdlib.h>
#include<stdio.h>
#include "node.h"
#include "forward_list.h"

struct ForwardList
{
    Node *head;
    int size;
};

ForwardList *forward_list_construct(){
    ForwardList *frwd_list = (ForwardList *)malloc(sizeof(ForwardList));
    frwd_list->head= NULL;
    frwd_list->size = 0;
    return frwd_list;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_push_front(ForwardList *l, void* data){
    Node * N = node_construct(data, l->head);
    l->head = N;
    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(void*)){
    Node* reference = l->head;

    printf("[");
    while(l->head != NULL){
        print_fn(node_get_value(l->head));
        if(node_get_next(l->head) != NULL) 
            printf(", "); 

        l->head = node_get_next(l->head);
    }
    printf("]");
    l->head = reference;
}

Node* forward_list_get_head_node(ForwardList *l){
    return l->head;
}

void* forward_list_get_head_value(ForwardList *l){
    return node_get_value(l->head);
}

Node* forward_list_get_node(ForwardList *l, int i){
    int count = 0;
    int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            l->head = reference;
            return l->head;
        }
        l->head = node_get_next(l->head);
        count++;
    }
    return NULL;
}


void* forward_list_get(ForwardList *l, int i){
    int count = 0;
    void* val = 0;
    int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            val = node_get_value(l->head);
            l->head = reference;
            return val;
        }
        l->head = node_get_next(l->head);
        count++;
    }
    return val;
}

void* forward_list_pop_front(ForwardList *l){
    Node* reference = node_get_next(l->head);
    void* val = node_get_value(l->head);
    free(l->head);

    l->head = reference;
    l->size--;

    return val;
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList* reversed_list = forward_list_construct();
    int size = forward_list_size(l), count = 0;
    void* value;
    while(count < size){
        value = forward_list_get(l, count);
        forward_list_push_front(reversed_list, value);
        count++;
    }
    return reversed_list;
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node* reference = l->head;
    while(l->head != NULL){
        l->head = node_get_next(l->head);
    }
    l->head = m->head;
    l->head = reference;
}

void forward_list_destroy(ForwardList *l){
    node_destroy_recursive(l->head);
    free(l);
}