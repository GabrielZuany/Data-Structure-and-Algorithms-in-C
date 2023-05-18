#include<stdlib.h>
#include<stdio.h>
#include "node.h"
#include "list.h"

void node_destroy_recursive(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_recursive(n->next);
    free(n);
}

List *list_construct(){
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

int list_size(List *l){
    return l->size;
}

void list_push_front(List *l, data_type data){
    Node * N = node_construct(data, l->head, NULL);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }else{
       l->head->prev = N;
    }
    l->head = N;
    l->size++;
    
}

void list_push_back(List *l, data_type data){
    Node * N = node_construct(data, NULL, l->last);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }
    else{
        l->last->next = N;
        l->last = l->last->next;
    }
    l->size++;
}

void list_print(List *l, void (*print_fn)(data_type)){
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

void list_print_reverse(List *l, void (*print_fn)(data_type)){
    Node* last_ref = l->last;

    printf("[");
    while(last_ref != NULL){
        print_fn(last_ref->value);
        if(last_ref->prev != NULL) 
            printf(", "); 

        last_ref = last_ref->prev;
    }
    printf("]");
}

data_type list_get(List *l, int i){
    int count = 0;
    data_type val = 0;
    int len = list_size(l);
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

data_type list_pop_front(List *l){
    Node* reference = l->head->next;
    data_type val = l->head->value;
    
    free(l->head);

    l->head = reference;
    if(l->head != NULL)
        l->head->prev = NULL;
    l->size--;

    return val;
}

data_type list_pop_back(List *l){
    Node* reference = l->last->prev;
    data_type val = l->last->value;
    
    free(l->last);

    l->last = reference;
    if(l->last != NULL)
        l->last->next = NULL;
    l->size--;

    return val;
}

List *list_reverse(List *l){
    List* reversed_list = list_construct();
    int size = list_size(l), count = 0;
    data_type value;
    while(count < size){
        value = list_get(l, count);
        list_push_front(reversed_list, value);
        count++;
    }
    return reversed_list;
}

void list_clear(List *l);

int list_exists(List *l, data_type val){
    int count = 0;
    int len = list_size(l);
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

void list_remove(List *l, data_type val){
    Node *n = l->head, *prev = NULL,*new_n = NULL;

    while (n != NULL) {
        if (n->value == val) {
            if (prev == NULL)
                l->head = new_n = n->next;
            else
                prev->next = new_n = n->next;

            node_destroy(n);
            n = new_n;
            l->size--;
        }
        else {
            prev = n;
            n = n->next;
        }
    }
}

void list_cat(List *l, List *m){
    Node* reference = l->head;
    while(l->head != NULL){
        l->head = l->head->next;
    }
    l->head = m->head;
    l->head = reference;
}

void list_sort(List *l);

void list_destroy(List *l){
    node_destroy_recursive(l->head);
    free(l);
}
