
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

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

void celula_print(void *c)
{   
    Celula *cel = (Celula *)c;
    printf("(%d,%d)", cel->x, cel->y);
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
            deque_push_back(d, celula_create(x, y));
        }
        else if (!strcmp(cmd, "PUSH_FRONT"))
        {
            scanf("%d %d", &x, &y);
            deque_push_front(d, celula_create(x, y));
        }
        else if (!strcmp(cmd, "POP_BACK"))
        {
            Celula *c = deque_pop_back(d);
            printf("%d %d\n", c->x, c->y);
            celula_free(c);
        }
        else if (!strcmp(cmd, "POP_FRONT"))
        {
            Celula *c = deque_pop_front(d);
            printf("%d %d\n", c->x, c->y);
            celula_free(c);
        }
        /*if(!strcmp(cmd, "PUSH_FRONT")){
            deque_push_front(d, (void *)i+1);
        }
        else if(!strcmp(cmd, "PUSH_BACK")){
            deque_push_back(d, (void *)i+1);
        }
        else if(!strcmp(cmd, "POP_FRONT")){
            printf("%d\n", deque_pop_front(d));
        }
        else if(!strcmp(cmd, "POP_BACK")){
            printf("%d\n", deque_pop_back(d));
        }*/
        
        //deque_print(d, NULL);
    }

    deque_destroy(d);
    return 0;
}