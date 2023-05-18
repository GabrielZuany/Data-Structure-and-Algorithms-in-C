#include "lib/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

int main() {
    
    srand(time(NULL));
    int x = rand();

    Vector *v = vector_construct();
    int count = 0;
    int n = 1;//tamanho do vetor variando de 1 a 2000 variando de 200 em 200
    int iterator = 200;
    int idx; //indice aleatorio
    int valor; // valor do indice aleatorio
    int m = 1000; // numero de buscas de elementos
    int k;
    double inicio;
    double fim;
    double duracao; 
    double total = 0, maior = 0, menor = 0, media = 0;


    while(n<2001){
        k=n;
        for (count = 0; count < n; count++) {
            srand(time(NULL));
            x = rand();
            vector_push_back(v, count);
            k--;
        }

        for (count=0; count<m; count++){
            idx = rand() % n;
            valor = vector_get(v, idx);
            
            inicio = get_timestamp();
            
            fim = get_timestamp();
            duracao = fim - inicio; 

            total+=duracao;

            if (count==0){
                maior = duracao;
                menor = duracao;
                continue;
            }

            if(duracao>maior){
                maior = duracao;
                continue;
            }
            if (duracao<menor){
                menor=duracao;
                continue;
            }
        }

        media = total/m;
        total = 0;
        
        printf("%d,%.8lf,%.8lf,%.8lf\n", n, menor, maior, media);

        vector_destroy(v);
        v = vector_construct();

        n*=2;
    }

    vector_destroy(v);

    return 0;
}