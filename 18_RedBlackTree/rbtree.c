#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    Key key;
    Value val;
    bool color;
    RBT *l, *r;
};
compare_t compare;

RBT *create_node(Key key, Value val, bool color)
{
    RBT *n = malloc(sizeof(RBT));
    n->key = key;
    n->val = val;
    n->color = color;
    n->l = NULL;
    n->r = NULL;
    return n;
}

RBT *RBinit(compare_t compare_func){
    RBT *h = malloc(sizeof(RBT));
    h->color = BLACK;
    h->l = NULL;
    h->r = NULL;
    compare = compare_func;
    return h;
}

bool is_red(RBT *x)
{
    if (x == NULL)
        return BLACK;
    return x->color; // RED == true
}

RBT *RBT_insert(RBT *h, Key key, Value val)
{
    // Insert at bottom and color it red.
    if (h == NULL) { return create_node(key, val, RED); }

    int cmp = compare(key, h->key);

    if (cmp < 0)        { h->l = RBT_insert(h->l, key, val); }
    else if (cmp > 0)   { h->r = RBT_insert(h->r, key, val); }
    else /*cmp == 0*/   { h->val = val; }

    // Lean left.
    if (is_red(h->r) && !is_red(h->l))   { h = rotate_left(h); }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l)) { h = rotate_right(h); }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r))    { flip_colors(h); }

    return h;
}

Value search(RBT *n, Key key)
{
    while (n != NULL)
    {
        int cmp;
        cmp = compare(key, n->key);
        if (cmp < 0)
            n = n->l;
        else if (cmp > 0)
            n = n->r;
        else
            return n->val;
    }
    return NULL;
}

RBT *rotate_left(RBT *h)
{
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT *rotate_right(RBT *h)
{
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT *h)
{
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}
