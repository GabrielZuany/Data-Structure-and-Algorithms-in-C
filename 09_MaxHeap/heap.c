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
    void (*destructor_fn)(void*, ...);
};

Heap* heap_construct(void (*DatatypeDestructorFn)(void *, ...)) {
    Heap* heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    heap->destructor_fn = DatatypeDestructorFn;
    return heap;
}

void node_swap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up( Heap *heap, int idx){
    if(idx == 0){
        return;
    }

    HeapNode *current = &heap->nodes[idx];
    HeapNode *parent = &heap->nodes[_parent_idx_(idx)];

    if(current->priority > parent->priority){
        node_swap(current, parent);
        heapify_up(heap, _parent_idx_(idx));
    }
}

void heapify_down(Heap *heap, int idx) {
    int left_child_idx = _left_child_idx_(idx);
    int right_child_idx = _right_child_idx_(idx);
    int largest = idx;

    if (left_child_idx < heap->size &&
        heap->nodes[left_child_idx].priority > heap->nodes[largest].priority) {
        largest = left_child_idx;
    }

    if (right_child_idx < heap->size &&
        heap->nodes[right_child_idx].priority > heap->nodes[largest].priority) {
        largest = right_child_idx;
    }

    if (largest != idx) {
        node_swap(&heap->nodes[idx], &heap->nodes[largest]);
        heapify_down(heap, largest);
    }
}

void heap_push(Heap *heap, void *data, double priority){

    if(heap->size == heap->capacity){
        heap->capacity *= 2;
        heap->nodes = realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if(heap->size == 1){
        return;
    }

    heapify_up(heap, heap->size - 1);
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

double heap_max_priority(Heap *heap){
    return heap->nodes[0].priority;
}

void *heap_pop(Heap *heap){
    if(heap->size == 0){
        return NULL;
    }

    void *data = heap->nodes[0].data;
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;

    heapify_down(heap, 0);

    return data;
}

void heap_destroy(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        heap->destructor_fn(heap->nodes[i].data);
    }
    free(heap->nodes);
    free(heap);
}
void heap_sort(Heap *heap){
    void (*DatatypeDestructorFn)(void *, ...) = heap->destructor_fn;
    Heap* temp = heap_construct(DatatypeDestructorFn);
    memcpy(temp->nodes, heap->nodes, sizeof(HeapNode) * heap->size);
    temp->size = heap->size;
    
    for(int i = 0; i < heap->size; i++){
        heap->nodes[i] = temp->nodes[0];
        heap_pop(temp);
    }
    heap_destroy(temp);
}

void heap_print(Heap *heap, void (*print_fn)(void *)){
    int i = 0;
    for(i = 0; i < heap->size; i++){
        print_fn(heap->nodes[i].data);
    }
    printf("\n");
}