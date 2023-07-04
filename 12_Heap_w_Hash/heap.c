#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "heap.h"
#include "hash.h"

#define CAPACITY 15
#define _parent_idx_(idx) ((idx - 1) / 2)
#define _left_child_idx_(idx) (2 * idx + 1)
#define _right_child_idx_(idx) (2 * idx + 2)

typedef struct HeapNode {
    void* data;
    double priority;
    int arr_idx;
} HeapNode;

typedef struct Heap {
    HeapNode* nodes;
    int size;
    int capacity;
    void (*destructor_fn)(void*, ...);
    HashTable* hash_table; //guarda a celula(key) e a posicao no heap(val)
} Heap;

// Function to swap two heap nodes
void node_swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap* heap, int idx) {
    if (idx == 0) {
        return;
    }

    HeapNode* current = &heap->nodes[idx];
    HeapNode* parent = &heap->nodes[_parent_idx_(idx)];

    if (current->priority < parent->priority) {
        node_swap(current, parent);
        heapify_up(heap, _parent_idx_(idx));
    }
}

void heapify_down(Heap* heap, int idx) {
    int left_child_idx = _left_child_idx_(idx);
    int right_child_idx = _right_child_idx_(idx);
    int smallest = idx;

    if (left_child_idx < heap->size &&
        heap->nodes[left_child_idx].priority < heap->nodes[smallest].priority) {
        smallest = left_child_idx;
    }

    if (right_child_idx < heap->size &&
        heap->nodes[right_child_idx].priority < heap->nodes[smallest].priority) {
        smallest = right_child_idx;
    }

    if (smallest != idx) {
        node_swap(&heap->nodes[idx], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

Heap* heap_construct(void (*DatatypeDestructorFn)(void *, ...), HashTable* hash_table) {
    Heap* heap = malloc(sizeof(Heap));
    heap->hash_table = hash_table;
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    heap->destructor_fn = DatatypeDestructorFn;
    return heap;
}

void* heap_push(Heap* heap, void* data, double priority) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if (heap->size == 1) {
        return NULL;
    }

    heapify_up(heap, heap->size - 1);
}

HeapNode* heap_left_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_left_child_idx_(node->arr_idx)];
}

HeapNode* heap_right_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_right_child_idx_(node->arr_idx)];
}

HeapNode* heap_parent_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_parent_idx_(node->arr_idx)];
}

int heap_empty(Heap* heap) {
    return heap->size == 0;
}

void* heap_min(Heap* heap) {
    return heap->nodes[0].data;
}

double heap_min_priority(Heap* heap) {
    return heap->nodes[0].priority;
}

void* heap_pop(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }

    void* data = heap->nodes[0].data;
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

void heap_print(Heap* heap, void (*print_fn)(void*)) {
    int i = 0;
    for (i = 0; i < heap->size; i++) {
        print_fn(heap->nodes[i].data);
    }
    printf("\n");
}
