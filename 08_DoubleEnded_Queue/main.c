#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include <string.h>

typedef struct
{
    int x, y;
} Celula;

Celula *celula_create(int x, int y)
{
    Celula *c = malloc(sizeof(Celula));
    c->x = x;
    c->y = y;
    return c;
}

void celula_free(Celula *c)
{
    free(c);
}


int main()
{
    int i, n, x, y;
    char cmd[10];
    Deque *d = deque_create();

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "PUSH_BACK"))
        {
            scanf("%d %d", &x, &y);
            deque_push_front(d, celula_create(x, y));
        }
        else if (!strcmp(cmd, "PUSH_FRONT"))
        {
            scanf("%d %d", &x, &y);
            deque_push_back(d, celula_create(x, y));
        }
        else if (!strcmp(cmd, "POP_BACK"))
        {
            Celula *c = deque_pop_front(d);
            printf("%d %d\n", c->x, c->y);
            celula_free(c);
        }
        else if (!strcmp(cmd, "POP_FRONT"))
        {
            Celula *c = deque_pop_back(d);
            printf("%d %d\n", c->x, c->y);
            celula_free(c);
        }   
    }

    deque_destroy(d);
    return 0;
}