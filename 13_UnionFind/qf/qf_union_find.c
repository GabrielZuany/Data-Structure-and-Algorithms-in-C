#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "qf_union_find.h"

struct UnionFind
{
    int* data;
    int length;
};

UnionFind* init(int n){
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->data = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        uf->data[i] = i;
    }
    uf->length = n;
    return uf;
}

void destroy(UnionFind* uf){
    free(uf->data);
    free(uf);
}

bool isConnected(UnionFind* uf, int p, int q){
    return find(uf, p) == find(uf, q);
}

int find(UnionFind* uf, int p){
    return uf->data[p];
}

void connect(UnionFind* uf, int p, int q){
    int pId = find(uf, p);
    int qId = find(uf, q);

    if(pId == qId){
        return;
    }

    for(int i = 0; i < uf->length; i++){
        if(uf->data[i] == pId){
            uf->data[i] = qId;
        }
    }
}