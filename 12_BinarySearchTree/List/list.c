#include<stdlib.h>
#include<stdio.h>
#include "dll_node.h"
#include "list.h"

struct List
{
    dll_node *head;
    dll_node *last;
    int size;
};

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

void* list_get_first(List *l){
    return dll_node_get_data(l->head);
}

void* list_get_last(List *l){
    return dll_node_get_data(l->last);
}

void list_push_front(List *l, void* data){
    dll_node * N = dll_node_construct(data, l->head, NULL);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }else{
        dll_node_set_prev(l->head, N);
    }
    l->head = N;
    l->size++;
    
}

void list_push_back(List *l, void* data){
    dll_node * N = dll_node_construct(data, NULL, l->last);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }
    else{
        dll_node_set_next(l->last, N);
        l->last = dll_node_get_next(l->last);
    }
    l->size++;
}

void list_print(List *l, void (*print_fn)(void*)){
    dll_node* reference = l->head;

    printf("[");
    while(l->head != NULL){
        print_fn(dll_node_get_data(l->head));
        if(dll_node_get_next(l->head) != NULL) 
            printf(", "); 

        l->head = dll_node_get_next(l->head);
    }
    printf("]");
    l->head = reference;
}

void list_print_reverse(List *l, void (*print_fn)(void*)){
    dll_node* last_ref = l->last;

    printf("[");
    while(last_ref != NULL){
        print_fn(dll_node_get_data(last_ref));
        if(dll_node_get_prev(last_ref) != NULL) 
            printf(", "); 

        last_ref = dll_node_get_prev(last_ref);
    }
    printf("]");
}

void* list_get(List *l, int i){
    int count = 0;
    void* val = 0;
    int len = list_size(l);
    dll_node* reference = l->head;

    while(count < len){
        if(count == i){
            val = dll_node_get_data(l->head);
            l->head = reference;
            return val;
        }
        l->head = dll_node_get_next(l->head);
        count++;
    }
    return val;
}

void* list_pop_front(List *l){
    dll_node* reference = dll_node_get_next(l->head);
    void* val = dll_node_get_data(l->head);
    
    free(l->head);

    l->head = reference;
    if(l->head != NULL)
        dll_node_set_prev(l->head, NULL);
    l->size--;

    return val;
}

void* list_pop_back(List *l){
    dll_node* reference = dll_node_get_prev(l->last);
    void* val = dll_node_get_data(l->last);
    
    if(l->last != NULL)
        dll_node_destroy(l->last);

    l->last = reference;
    if(l->last != NULL)
        dll_node_set_next(l->last, NULL);
    l->size--;

    return val;
}

List *list_reverse(List *l){
    List* reversed_list = list_construct();
    int size = list_size(l), count = 0;
    void* value;
    while(count < size){
        value = list_get(l, count);
        list_push_front(reversed_list, value);
        count++;
    }
    return reversed_list;
}

void list_cat(List *l, List *m){
    dll_node* reference = l->head;
    while(l->head != NULL){
        l->head = dll_node_get_next(l->head);
    }
    l->head = m->head;
    l->head = reference;
}

void* list_back(List *l){
    return l->last;
}

void list_destroy(List *l){
    if(l->head == NULL){
        return;
    }
    if(l->head == NULL){
        free(l);
        return;
    }
    dll_node_destroy_recursive(l->head);
    free(l);
}
