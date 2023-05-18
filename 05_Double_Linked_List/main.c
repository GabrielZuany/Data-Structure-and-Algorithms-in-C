
#include <stdio.h>

#include "list.h"

int main()
{
    int n, val;

    List *l = list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        list_push_back(l, val);
    }

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        printf("%d\n", list_pop_back(l));

    // test the destroy function
    list_destroy(l);

    return 0;
}