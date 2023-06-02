#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "circular_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Deque Deque;

Deque *deque_new(int define_total_capacity);

void deque_delete(Deque *d);

void deque_push_front(Deque *d, int value);

void deque_push_back(Deque *d, int value);

void deque_pop_front(Deque *d);

void deque_pop_back(Deque *d);

int deque_get(Deque *d, int index);

void deque_print(Deque *d);

#endif