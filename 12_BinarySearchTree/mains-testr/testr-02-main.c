
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

typedef struct
{
    int x, y;
} Cell;

Cell *cell_construct(int x, int y)
{
    Cell *p = (Cell *)calloc(1, sizeof(Cell));

    p->x = x;
    p->y = y;

    return p;
}

void cell_destroy(Cell *c)
{
    free(c);
}

int cmp_fn(void *a, void *b)
{
    Cell *cell_a = a;
    Cell *cell_b = b;

    if (cell_a->y < cell_b->y)
        return -1;
    else if (cell_a->y > cell_b->y)
        return 1;
    else
    {
        if (cell_a->x < cell_b->x)
            return -1;
        else if (cell_a->x > cell_b->x)
            return 1;
        else
            return 0;
    }
}

void key_destroy_fn(void *key)
{
    free(key);
}

void val_destroy_fn(void *val)
{
    cell_destroy(val);
}

int *new_int(int idx)
{
    int *p = (int *)calloc(1, sizeof(int));
    *p = idx;
    return p;
}

int main()
{
    int i, n, idx, x, y;
    char op[20];

    scanf("%d", &n);

    BinaryTree *bt = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", op);

        if (!strcmp(op, "SET"))
        {
            scanf("%d %d %d", &x, &y, &idx);
            binary_tree_add(bt, cell_construct(x, y), new_int(idx));
        }
        else
        {
            scanf("%d %d", &x, &y);
            Cell *c = cell_construct(x, y);
            int *p = binary_tree_get(bt, c);
            printf("%d\n", *p);
            cell_destroy(c);
        }
    }

    binary_tree_destroy(bt);

    return 0;
}