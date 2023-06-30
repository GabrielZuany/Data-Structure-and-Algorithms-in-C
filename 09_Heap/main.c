#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"

typedef struct Person{
    char name[20];
    int age;
} Person;

void print_person(void *data){
    Person *person = data;
    printf("%s %d | ", person->name, person->age);
}

void print_int(void *data){
    int *x = data;
    printf("%d |", *x);
}

int main(){

    Heap *heap = heap_construct();

    int i = 0, n;
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        //Person *person = malloc(sizeof(Person));
        //char name[20];
        //printf("Enter name: ");
        //scanf("%s", name);
        //strcpy(person->name, name);
        //printf("Enter age: ");
        //scanf("%d", &person->age);
        //heap_push(heap, person, person->age);
        //heap_print(heap, print_person); 
        int *x = malloc(sizeof(int));
        scanf("%d", x);
        heap_push(heap, x, *x);
        heap_print(heap, print_int);
    }

    printf("\n");

    char cmd[10];
    for(i = 0; i < n; i++){
        //Person *person = heap_pop(heap);
        //printf("%s %d\n", person->name, person->age);
        //free(person);
        scanf("%s", cmd);
        if(strcmp(cmd, "POP")==0){
            int *x = heap_pop(heap);
            printf("POP %d\n", *x);
        }
        heap_print(heap, print_int);
    }



    return 0; 
}

