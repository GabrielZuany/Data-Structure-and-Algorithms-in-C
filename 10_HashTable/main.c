
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

int celula_hash(HashTable *h, void *key)
{
    Celula *c = (Celula *)key;
    // 83 e 97 sao primos e o operador "^" é o XOR bit a bit
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
            hash_table_set(h, cel, pos);
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

    /*HashTableIterator *it = hash_table_iterator(h);

    while (!hash_table_iterator_is_over(it))
    {
        HashTableItem *item = hash_table_iterator_next(it);
        Celula *cel = (Celula *)item->key;
        int *pos = (int *)item->val;
        celula_destroy(cel);
        free(pos);
    }

    hash_table_iterator_destroy(it);
    hash_table_destroy(h);*/

    return 0;
}