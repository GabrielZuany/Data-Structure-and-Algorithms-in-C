#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

Deque* deque_create();

void deque_destroy(Deque* d);

int deque_empty(Deque* d);

void __deque_destroy_chunks(Deque* d);

void deque_push_front(Deque* d, void* data);

void deque_push_back(Deque* d, void* data);

void* deque_pop_front(Deque* d);

void* deque_pop_back(Deque* d);

void deque_print(Deque* d, void (*print)(void*));

#endif
