#include <stdio.h>
#include <stdlib.h>
#include "union_find.h"

int main(int argc, char *argv[]) {
    int p, q;
    int n = 10;
    UnionFind* uf = init(n);
    while(scanf("%d %d", &p, &q) == 2){
        if(!isConnected(uf, p, q)){
            connect(uf, p, q);
            printf("%d %d\n", p, q);
        }
    }
    return 0;
}