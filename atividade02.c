
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *vetor, int inicio, int meio, int fim, int *comparacoes) {
    int tamanho1 = (meio - inicio + 1);
    int tamanho2 = (fim - meio);
    int i, j;

    int *esquerda = (int*)malloc(sizeof(int) * (tamanho1 + 1));
    int *direita = (int*)malloc(sizeof(int) * (tamanho2 + 1));

    for (i = 0; i < tamanho1; i++)
        esquerda[i] = vetor[inicio + i];
    for (j = 0; j < tamanho2; j++)
        direita[j] = vetor[meio + 1 + j];

    esquerda[tamanho1] = INT_MAX;
    direita[tamanho2] = INT_MAX;

    i = 0;
    j = 0;

    for (int k = inicio; k <= fim; k++) {
        (*comparacoes)++;
        if (esquerda[i] <= direita[j])
            vetor[k] = esquerda[i++];
        else
            vetor[k] = direita[j++];
    }

    free(esquerda);
    free(direita);
}

void mergeSort(int *vetor, int inicio, int fim, int *comparacoes) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio, comparacoes);
        mergeSort(vetor, meio + 1, fim, comparacoes);
        merge(vetor, inicio, meio, fim, comparacoes);
    }
}

int mediana(int *vetor, int inicio, int fim, int *comparacoes) {
    int meio = inicio + (fim - inicio) / 2;

    int a = vetor[inicio];
    int b = vetor[meio];
    int c = vetor[fim];
    
    (*comparacoes) += 3;

    if ((a > b && a < c) || (a > c && a < b))
        return inicio;
    else if ((b > a && b < c) || (b > c && b < a))
        return meio;
    else
        return fim;
}

int particionar(int *vetor, int inicio, int fim, int *comparacoes) {
    int indicePivo = mediana(vetor, inicio, fim, comparacoes);
    troca(&vetor[indicePivo], &vetor[fim]);
    int pivo = vetor[fim];

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        (*comparacoes)++;
        if (vetor[j] <= pivo) {
            i++;
            troca(&vetor[i], &vetor[j]);
        }
    }

    troca(&vetor[i + 1], &vetor[fim]);
    return i + 1;
}

void quickSort(int *vetor, int inicio, int fim, int *comparacoes) {
    if (inicio < fim) {
        int pivo = particionar(vetor, inicio, fim, comparacoes);
        quickSort(vetor, inicio, pivo - 1, comparacoes);
        quickSort(vetor, pivo + 1, fim, comparacoes);
    }
}

void insertionSort(int *vetor, int inicio, int fim, int *comparacoes) {
    for (int i = inicio + 1; i <= fim; i++) {
        int chave = vetor[i];
        int j = i - 1;

        while (j >= inicio && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            (*comparacoes)++;
            j--;
        }
        
        if (j >= inicio) (*comparacoes)++;

        if (j + 1 != i)
            vetor[j + 1] = chave;
    }
}

void hibrido(int *vetor, int inicio, int fim, int *comparacoes) {
    if (inicio < fim) {
        if ((fim - inicio + 1) <= 5)
            insertionSort(vetor, inicio, fim, comparacoes);
        else {
            int pivo = particionar(vetor, inicio, fim, comparacoes);
            hibrido(vetor, inicio, pivo - 1, comparacoes);
            hibrido(vetor, pivo + 1, fim, comparacoes);
        }
    }
}

int *copiarVetor(int *vetor, int tamanho) {
    int *copia = (int*)malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++)
        copia[i] = vetor[i];

    return copia;
}

void troca(int *num1, int *num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void imprimirVetor(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

int main() {
    int *vetor, tamanho;
    int comparacoes = 0;

    scanf("%d", &tamanho);
    
    vetor = (int*)malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++)
        scanf("%d", &vetor[i]);

    int *vetorCopia = copiarVetor(vetor, tamanho);
    mergeSort(vetorCopia, 0, (tamanho - 1), &comparacoes);
    imprimirVetor(vetorCopia, tamanho);
    printf("%d\n", comparacoes);
    free(vetorCopia);
    
    vetorCopia = copiarVetor(vetor, tamanho);
    comparacoes = 0;
    quickSort(vetorCopia, 0, (tamanho - 1), &comparacoes);
    imprimirVetor(vetorCopia, tamanho);
    printf("%d\n", comparacoes);
    free(vetorCopia);

    vetorCopia = copiarVetor(vetor, tamanho);
    comparacoes = 0;
    hibrido(vetorCopia, 0, (tamanho - 1), &comparacoes);
    imprimirVetor(vetorCopia, tamanho);
    printf("%d\n", comparacoes);
    free(vetorCopia);

    free(vetor);
    return 0;
}
