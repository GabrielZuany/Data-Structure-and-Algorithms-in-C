
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

typedef struct
{
    char *name;
    char *cpf;
    int idade;
    float altura;
} Person;

Person *person_construct(const char *name, const char *cpf, int idade, float altura)
{
    Person *p = (Person *)calloc(1, sizeof(Person));

    p->name = (char *)calloc(strlen(name) + 1, sizeof(char));
    p->cpf = (char *)calloc(strlen(cpf) + 1, sizeof(char));
    p->idade = idade;
    p->altura = altura;

    memcpy(p->name, name, (strlen(name) + 1) * sizeof(char));
    memcpy(p->cpf, cpf, (strlen(cpf) + 1) * sizeof(char));

    return p;
}

void person_destroy(Person *p)
{
    free(p->name);
    free(p->cpf);
    free(p);
}

int cmp_fn(void *a, void *b)
{
    return strcmp(a, b);
}

void key_destroy_fn(void *key)
{
    free(key);
}

void val_destroy_fn(void *val)
{
    person_destroy((Person *)val);
}

int main()
{
    int i, n, idade;
    float altura;
    char op[20];
    char cpf[100];
    char nome[100];

    scanf("%d", &n);

    BinaryTree *bt = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", op);

        if (!strcmp(op, "SET"))
        {
            scanf("%s %s %d %f", cpf, nome, &idade, &altura);
            binary_tree_add(bt, strdup(cpf), person_construct(nome, cpf, idade, altura));
        }
        else if (!strcmp(op, "POP"))
        {
            scanf("%s", cpf);
            binary_tree_remove(bt, cpf);
        }
        else
        {
            scanf("%s", cpf);
            Person *p = binary_tree_get(bt, cpf);

            if (p == NULL)
                printf("CHAVE INEXISTENTE\n");
            else
                printf("%s %d %.2f\n", p->name, p->idade, p->altura);
        }
    }

    binary_tree_destroy(bt);

    return 0;
}