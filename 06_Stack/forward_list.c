#include<stdlib.h>
#include<stdio.h>
#include "node.h"
#include "forward_list.h"

void node_destroy_recursive(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_recursive(n->next);
    free(n);
}

ForwardList *forward_list_construct(){
    ForwardList *frwd_list = (ForwardList *)malloc(sizeof(ForwardList));
    frwd_list->head= NULL;
    frwd_list->size = 0;
    return frwd_list;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data){
    Node * N = node_construct(data, l->head);
    l->head = N;
    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node* reference = l->head;

    printf("[");
    while(l->head != NULL){
        print_fn(l->head->value);
        if(l->head->next != NULL) 
            printf(", "); 

        l->head = l->head->next;
    }
    printf("]");
    l->head = reference;
}

data_type forward_list_get(ForwardList *l, int i){
    int count = 0;
    data_type val = 0;
    int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            val = l->head->value;
            l->head = reference;
            return val;
        }
        l->head = l->head->next;
        count++;
    }
    return -999;
}

data_type forward_list_pop_front(ForwardList *l){
    Node* reference = l->head->next;
    data_type val = l->head->value;
    free(l->head);

    l->head = reference;
    l->size--;

    return val;
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList* reversed_list = forward_list_construct();
    int size = forward_list_size(l), count = 0;
    data_type value;
    while(count < size){
        value = forward_list_get(l, count);
        forward_list_push_front(reversed_list, value);
        count++;
    }
    return reversed_list;
}

void forward_list_clear(ForwardList *l){
    node_destroy(l->head);
}

int forward_list_exists(ForwardList *l, data_type val){
    int count = 0;
    int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(l->head->value == val){
            l->head = reference;
            return 1;
        }
        l->head = l->head->next;
        count++;
    }
    l->head = reference;
    return 0;
}

void forward_list_remove_one(ForwardList *l, data_type val){
    int count = 0;
    int len = forward_list_size(l);
    Node* reference = l->head;
    Node* next_node;
    while(count < len){
        if((count == 0) && l->head->value == val){
            reference = l->head->next;
            free(l->head); 
            l->head = reference;
            l->size--;
            return;
        }
        if(l->head->next->value == val){
            next_node = l->head->next->next;
            free(l->head->next);
            l->head->next = next_node;
            l->size--;
            l->head = reference;
            return;
        }
        l->head = l->head->next;
        count++;
    }
}

void forward_list_remove(ForwardList *l, data_type val){
    while(forward_list_exists(l, val)){
        forward_list_remove_one(l, val);
    }
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node* reference = l->head;
    while(l->head != NULL){
        l->head = l->head->next;
    }
    l->head = m->head;
    l->head = reference;
}

void forward_list_destroy(ForwardList *l){
    node_destroy_recursive(l->head);
    free(l);
}
