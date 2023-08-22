#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../05_Stack/stack.h"

int main(){

    Stack* numeric = stack_construct();
    Stack* operators = stack_construct();
    char str[100] = "";
    int res = 0;
    
    scanf("%s", str);
    int size = strlen(str);
    int v1, v2;
    for(int i = 0; i < size; i++){
        if(str[i] == '('){
            continue;
        }
        if(str[i] == ')'){
            switch(*(char*)stack_pop(operators)){
                case '+':
                    v1 = atoi((char*)stack_pop(numeric));
                    v2 = atoi((char*)stack_pop(numeric));
                    res =  v1 + v2;
                    break;
                case '-':
                    v1 = atoi((char*)stack_pop(numeric));
                    v2 = atoi((char*)stack_pop(numeric));
                    res =  v1 - v2;
                    break;
                case '*':
                    v1 = atoi((char*)stack_pop(numeric));
                    v2 = atoi((char*)stack_pop(numeric));
                    res =  v1 * v2;
                    break;
                case '/':
                    v1 = atoi((char*)stack_pop(numeric));
                    v2 = atoi((char*)stack_pop(numeric));
                    res =  v1 / v2;
                    break;
            }
        }
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            stack_push(operators, &str[i]);
        }
        else{
            stack_push(numeric, &str[i]);
        }
    }

    printf("RES %d\n", res);

    stack_destroy(numeric);
    stack_destroy(operators);

    return 0;
}