#include<stdio.h>
#include<stdlib.h>

void troca(int *A, int *B) {
    int aux = *A;
    *A = *B;
    *B = aux;
}

void merge(int vetor[], int comeco, int meio, int fim, int *comparacoes) {
    int grupo1 = meio - comeco + 1;
    int grupo2 = fim - meio;

    int *E = (int *)malloc(grupo1 * sizeof(int));
    int *D = (int *)malloc(grupo2 * sizeof(int));

    for(int i = 0; i < grupo1; i++) {
        E[i] = vetor[comeco + i];
    }
    for(int j = 0; j < grupo2; j++) {
        D[j] = vetor[meio + 1 + j];
    }

    int i = 0, j = 0, k = comeco;

    while(i < grupo1 && j < grupo2) {
        (*comparacoes)++;
        if(E[i] <= D[j]) {
            vetor[k] = E[i];
            i++;
        } else {
            vetor[k] = D[j];
            j++;
        }
        k++;
    }

    while(i < grupo1) {
        vetor[k] = E[i];
        i++;
        k++;
    }

    while(j < grupo2) {
        vetor[k] = D[j];
        j++;
        k++;
    }

    free(E);
    free(D);
}

void mergeSort(int vetor[], int comeco, int fim, int *comparacoes) {
    if(comeco < fim) {
        int meio = comeco + (fim - comeco)/2;
        mergeSort(vetor, comeco, meio, comparacoes);
        mergeSort(vetor, meio + 1, fim, comparacoes);
        merge(vetor, comeco, meio, fim, comparacoes);
    }
}

int calculaMediana(int vetor[], int comeco, int fim, int *comparacoes) {
    int meio = comeco + (fim - comeco)/2;
    
    (*comparacoes)++;
    if(vetor[comeco] > vetor[meio]) {
        troca(&vetor[comeco], &vetor[meio]);
    }
    
    (*comparacoes)++;
    if(vetor[comeco] > vetor[fim]) {
        troca(&vetor[comeco], &vetor[fim]);
    }
    
    (*comparacoes)++;
    if(vetor[meio] > vetor[fim]) {
        troca(&vetor[meio], &vetor[fim]);
    }
    
    return meio;
}

int dividir(int vetor[], int comeco, int fim, int *comparacoes) {
    int Enderecopivo = calculaMediana(vetor, comeco, fim, comparacoes);
    int pivo = vetor[Enderecopivo];
    
    troca(&vetor[Enderecopivo], &vetor[fim]);
    
    int i = comeco - 1;
    
    for(int j = comeco; j < fim; j++) {
        (*comparacoes)++;
        if(vetor[j] <= pivo) {
            i++;
            troca(&vetor[i], &vetor[j]);
        }
    }
    
    troca(&vetor[i + 1], &vetor[fim]);
    return i + 1;
}

void quickSort(int vetor[], int comeco, int fim, int *comparacoes) {
    if(comeco < fim) {
        int p = dividir(vetor, comeco, fim, comparacoes);
        quickSort(vetor, comeco, p - 1, comparacoes);
        quickSort(vetor, p + 1, fim, comparacoes);
    }
}

void insertionSort(int vetor[], int comeco, int fim, int *comparacoes) {
    for(int i = comeco + 1; i <= fim; i++) {
        int chave = vetor[i];
        int j = i - 1;
        
        while(j >= comeco && vetor[j] > chave) {
            (*comparacoes)++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        if(j >= comeco) (*comparacoes)++;
        vetor[j + 1] = chave;
    }
}

void hibrido(int vetor[], int comeco, int fim, int *comparacoes) {
    if(fim - comeco + 1 <= 5) {
        insertionSort(vetor, comeco, fim, comparacoes);
    } else {
        int p = dividir(vetor, comeco, fim, comparacoes);
        hibrido(vetor, comeco, p - 1, comparacoes);
        hibrido(vetor, p + 1, fim, comparacoes);
    }
}

int main() {
    int V;
    scanf("%d", &V);
    
    int *original = (int *)malloc(V * sizeof(int));
    int *copia1 = (int *)malloc(V * sizeof(int));
    int *copia2 = (int *)malloc(V * sizeof(int));
    
    for(int i = 0; i < V; i++) {
        scanf("%d", &original[i]);
        copia1[i] = original[i];
        copia2[i] = original[i];
    }

    int comparacoesMerge = 0;
    mergeSort(original, 0, V-1, &comparacoesMerge);
    if(V > 0) printf("%d", original[0]);
    for(int i = 1; i < V; i++) {
        printf(" %d", original[i]);
    }
    printf("\n%d\n", comparacoesMerge);

    int comparacoesQuick = 0;
    quickSort(copia1, 0, V-1, &comparacoesQuick);
    if(V > 0) printf("%d", copia1[0]);
    for(int i = 1; i < V; i++) {
        printf(" %d", copia1[i]);
    }
    printf("\n%d\n", comparacoesQuick);

    int comparacoesHibrido = 0;
    hibrido(copia2, 0, V-1, &comparacoesHibrido);
    if(V > 0) printf("%d", copia2[0]);
    for(int i = 1; i < V; i++) {
        printf(" %d", copia2[i]);
    }
    printf("\n%d\n", comparacoesHibrido);

    free(original);
    free(copia1);
    free(copia2);
    
    return 0;
}
