#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Heap;

// Function to swap two heap nodes
void node_swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform heapify up
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

// Function to perform heapify down
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

// Function to construct the heap
Heap* heap_construct() {
    Heap* heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    return heap;
}

// Function to push a new element into the heap
void heap_push(Heap* heap, void* data, double priority) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if (heap->size == 1) {
        return;
    }

    heapify_up(heap, heap->size - 1);
}

// Function to get the left child node of a given node
HeapNode* heap_left_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_left_child_idx_(node->arr_idx)];
}

// Function to get the right child node of a given node
HeapNode* heap_right_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_right_child_idx_(node->arr_idx)];
}

// Function to get the parent node of a given node
HeapNode* heap_parent_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_parent_idx_(node->arr_idx)];
}

// Function to check if the heap is empty
int heap_empty(Heap* heap) {
    return heap->size == 0;
}

// Function to get the minimum element from the heap
void* heap_min(Heap* heap) {
    return heap->nodes[0].data;
}

// Function to get the priority of the minimum element in the heap
double heap_min_priority(Heap* heap) {
    return heap->nodes[0].priority;
}

// Function to pop the minimum element from the heap
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

// Function to destroy the heap and free the allocated memory
void heap_destroy(Heap* heap) {
    free(heap->nodes);
    free(heap);
}

// Function to sort the elements in the heap (in-place)
void heap_sort(Heap* heap) {
    Heap* temp = heap_construct();
    memcpy(temp->nodes, heap->nodes, sizeof(HeapNode) * heap->size);
    temp->size = heap->size;

    for (int i = 0; i < heap->size; i++) {
        heap->nodes[i] = temp->nodes[0];
        heap_pop(temp);
    }
    heap_destroy(temp);
}

// Function to print the elements in the heap
void heap_print(Heap* heap, void (*print_fn)(void*)) {
    int i = 0;
    for (i = 0; i < heap->size; i++) {
        print_fn(heap->nodes[i].data);
    }
    printf("\n");
}
