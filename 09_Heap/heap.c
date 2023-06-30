#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 15
#define _parent_idx_(idx) ((idx - 1) / 2)
#define _left_child_idx_(idx) (2 * idx + 1)
#define _right_child_idx_(idx) (2 * idx + 2)

typedef struct HeapNode{
    void *data;
    double priority;
    int arr_idx;
} HeapNode;

struct Heap{
    HeapNode *nodes;
    int size;
    int capacity;
};


Heap *heap_construct(){
    Heap *heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    return heap;
}

void node_swap(HeapNode *a, HeapNode *b){
    int temp_idx = a->arr_idx;
    a->arr_idx = b->arr_idx;
    b->arr_idx = temp_idx;
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(Heap *heap, void *data, double priority){
    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if(heap->size == 1){
        return;
    }

    int new_node_idx = heap->size - 1;
    while(heap->nodes[new_node_idx].priority > heap->nodes[_parent_idx_(new_node_idx)].priority){
        HeapNode *parent = &heap->nodes[_parent_idx_(new_node_idx)];
        HeapNode *current = &heap->nodes[new_node_idx];
        node_swap(parent, current);
        new_node_idx = _parent_idx_(new_node_idx);
        current->arr_idx = new_node_idx;
    }
}

HeapNode* heap_left_child_node(Heap *heap, HeapNode *node){
    return &heap->nodes[_left_child_idx_(node->arr_idx)];
}

HeapNode* heap_right_child_node(Heap *heap, HeapNode *node){
    return &heap->nodes[_right_child_idx_(node->arr_idx)];
}

HeapNode* heap_parent_node(Heap *heap, HeapNode *node){
    return &heap->nodes[_parent_idx_(node->arr_idx)];
}    

Bool heap_empty(Heap *heap){
    return heap->size == 0;
}

void *heap_max(Heap *heap){
    return heap->nodes[0].data;
}

double heap_max_priority(Heap *heap); // O(1)

void *heap_pop(Heap *heap){
    if(heap->size == 0){
        return NULL;
    }

    void *data = heap->nodes[0].data;
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;

    int current_idx = 0;
    //while(1){
    //    HeapNode *current = &heap->nodes[current_idx];
    //    HeapNode *left_child = heap_left_child_node(heap, current);
    //    HeapNode *right_child = heap_right_child_node(heap, current);
//
    //    if(left_child->priority > current->priority && right_child->priority > current->priority){
    //        if(left_child->priority > right_child->priority){
    //            node_swap(current, left_child);
    //            current_idx = left_child->arr_idx;
    //        }else{
    //            node_swap(current, right_child);
    //            current_idx = right_child->arr_idx;
    //        }
    //    }else if(left_child->priority > current->priority){
    //        node_swap(current, left_child);
    //        current_idx = left_child->arr_idx;
    //    }else if(right_child->priority > current->priority){
    //        node_swap(current, right_child);
    //        current_idx = right_child->arr_idx;
    //    }else{
    //        break;
    //    } 
    //}

    return data;
}

void heap_destroy(Heap *heap); // O(1)

void heap_sort(void *array, int array_size, int item_size, double (*key_fn)(void *)); // O(N log N)

void heap_print(Heap *heap, void (*print_fn)(void *)){
    int i = 0;
    for(i = 0; i < heap->size; i++){
        print_fn(heap->nodes[i].data);
    }
    printf("\n");
}