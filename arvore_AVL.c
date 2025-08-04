#include<stdio.h>
#include<time.h>
#include<stdlib.h>

long int tam = 100000000; 


int busca_linear(long int v[], int tam, int x){
    for(int i = 0; i < tam; i++){
        if(v[i] == x){
            return i;
        }
    }
    return -1;
}

int busca_binaria1(long int v[], int tam, int x){
    int comeco = 0, final = tam - 1;

    while(comeco <= final){
        int meio = (comeco + final) / 2;

        if(v[meio] == x){
            return meio;
        }
        if(v[meio] < x){
            comeco = meio + 1;
        } else {
            final = meio - 1;
        }
    }
    return -1;
}

int busca_binaria2(long int v[], int comeco, int final, int x){
    int meio = comeco + (final - comeco) / 2;
    if(comeco < final){
        if(v[meio] == x){
           return meio;
        }
        if(v[meio] < x){
            return busca_binaria2(v, meio+1, final, x);
        } else {
            return busca_binaria2(v, comeco, meio - 1, x);
        }   
    }   
    return -1;

}

void trocar(long int *a, long int *b) {
    long int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(long int vetor[], int baixo, int alto) {
    long int pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (vetor[j] < pivo) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }

    trocar(&vetor[i + 1], &vetor[alto]);
    return (i + 1);
}

void quicksort(long int vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int indicePivo = particionar(vetor, baixo, alto);
        quicksort(vetor, baixo, indicePivo - 1);
        quicksort(vetor, indicePivo + 1, alto);
    }
}

int main(){

    long int *point = (long int *)malloc(sizeof(long int)*tam);

    clock_t tempo;

    srand((unsigned)time(NULL));

    for(int i = 0; i < tam; i++){
        point[i] = rand()%tam;
    }

    quicksort(point, 0, tam - 1);

    for(int i = 0; i < 20; i++){
        long int num = rand()%tam;

        tempo = clock();
        busca_linear(point, tam, num);
        tempo = clock() - tempo;

        printf("Tempo decorrido da busca linear: %.3f ms\n", ((double)tempo)/((CLOCKS_PER_SEC/1000)));

        tempo = clock();
        busca_binaria1(point, tam, num);
        tempo = clock() - tempo;

        printf("Tempo decorrido da busca binaria1: %.3f ms\n", ((double)tempo)/((CLOCKS_PER_SEC/1000)));

        tempo = clock();
        busca_binaria2(point, 0 , tam - 1, num);
        tempo = clock() - tempo;

        printf("Tempo decorrido da busca binaria2: %.3f ms\n", ((double)tempo)/((CLOCKS_PER_SEC/1000)));
    }


    return 0;
}
