#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

int main()
{
    int n, i, val;
    Stack *s = stack_construct();

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &val);
        stack_push(s, val);
    }

    while (!stack_empty(s))
        printf("%d\n", stack_pop(s));

    stack_destroy(s);
    return 0;
}