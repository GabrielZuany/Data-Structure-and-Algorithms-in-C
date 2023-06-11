#include <stdio.h>
#include <stdlib.h>
#include "../04_Double_Linked_List/node.h"

typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;

Deque* deque_create() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    return deque;
}

int deque_empty(Deque* deque) {
    return deque->front == NULL;
}

void deque_push_front(Deque* deque, void* data) {
    Node* newNode = node_construct(data, deque->front, NULL);
    if (deque_empty(deque)) {
        deque->rear = newNode;
    } else {
        node_set_prev(deque->front, newNode);
    }
    deque->front = newNode;
}

void deque_push_back(Deque* deque, void* data) {
    Node* newNode = node_construct(data, NULL, deque->rear);
    if (deque_empty(deque)) {
        deque->front = newNode;
    } else {
        node_set_next(deque->rear, newNode);
    }
    deque->rear = newNode;
}

void deque_pop_front(Deque* deque) {
    if (deque_empty(deque)) {
        printf("Deque is empty.\n");
        return;
    }

    Node* frontNode = deque->front;
    deque->front = node_get_next(frontNode);

    if (deque->front == NULL)
        deque->rear = NULL;
    else
        node_set_prev(deque->front, NULL);

    node_destroy(frontNode);
}

void deque_pop_back(Deque* deque) {
    if (deque_empty(deque)) {
        printf("Deque is empty.\n");
        return;
    }

    Node* rearNode = deque->rear;
    deque->rear = node_get_prev(rearNode);

    if (deque->rear == NULL)
        deque->front = NULL;
    else
        node_set_next(deque->rear, NULL);

    node_destroy(rearNode);
}

void deque_print(Deque* deque, void (*printData)(void*)) {
    if (deque_empty(deque)) {
        printf("Deque is empty.\n");
        return;
    }

    Node* current = deque->front;
    while (current != NULL) {
        printData(node_get_data(current));
        current = node_get_next(current);
    }
    printf("\n");
}

void freeDeque(Deque* deque) {
    while (!deque_empty(deque))
        deque_pop_front(deque);
    free(deque);
}