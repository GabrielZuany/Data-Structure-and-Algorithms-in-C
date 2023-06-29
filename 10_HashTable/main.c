#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

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

void celula_destroy(Celula *c)
{
    free(c);
}

// Wrapper functions to destroy the key and value without using iterators (só pra corrigir os parâmetros de chamada)
// funciona sem, mas acusa warning
void celula_destroy_wrapper(void *key, ...)
{
    celula_destroy((Celula *)key);
}

void free_wrapper(void *val, ...)
{
    free(val);
}

int celula_hash(HashTable *h, void *key)
{
    Celula *c = (Celula *)key;
    return ((c->x * 83) ^ (c->y * 97)) % hash_table_size(h);
}

int celula_cmp(void *c1, void *c2)
{
    Celula *a = (Celula *)c1;
    Celula *b = (Celula *)c2;

    if (a->x == b->x && a->y == b->y)
        return 0;
    else
        return 1;
}


int main()
{
    int i, n, x, y;
    char cmd[10];

    HashTable *h = hash_table_construct(19, celula_hash, celula_cmp);

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "SET"))
        {
            int *pos = malloc(sizeof(int));
            scanf("%d %d %d", &x, &y, pos);
            Celula *cel = celula_create(x, y);
            void *prev = hash_table_set(h, cel, pos);

            if (prev != NULL)
            {   
                celula_destroy(cel);
            }
        }
        else if (!strcmp(cmd, "GET"))
        {
            scanf("%d %d", &x, &y);
            Celula *cel = celula_create(x, y);
            int *pos = hash_table_get(h, cel);
            printf("%d\n", *pos);
            celula_destroy(cel);
        }
    }

    hash_table_destroy(h, celula_destroy_wrapper, free_wrapper);

    return 0;
}