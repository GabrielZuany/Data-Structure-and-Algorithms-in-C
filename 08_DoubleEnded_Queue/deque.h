#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "circular_vector.h"

typedef struct Deque Deque;

Deque *deque_new();

void deque_delete(Deque *deque);

int deque_size(Deque *deque);

int deque_allocated(Deque *deque);

void deque_push_front(Deque *deque, int value);

void deque_push_back(Deque *deque, int value);

void deque_pop_front(Deque *deque);

void deque_pop_back(Deque *deque);

void deque_print(Deque *deque);

#endif