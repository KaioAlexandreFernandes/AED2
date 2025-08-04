
#include <stdlib.h>
#include <stdio.h>

void troca(int *a, int *b, int *trocas) {
    if (a != b) {
        int aux = *a;
        *a = *b;
        *b = aux;
        (*trocas)++;
    }
}

void selectionSort(int array[], int tam, int *comparacoes, int *trocas) {
    for (int i = 0; i < tam - 1; i++) {
        int minimo = i;
        for (int j = i + 1; j < tam; j++) {
            (*comparacoes)++;
            if (array[j] < array[minimo]) {
                minimo = j;
            }
        }
        troca(&array[i], &array[minimo], trocas);
    }
}

void bubbleSort(int array[], int tam, int *comparacoes, int *trocas) {
    int trocado;
    for (int i = 0; i < tam - 1; i++) {
        trocado = 0;
        for (int j = 0; j < tam - i - 1; j++) {
            (*comparacoes)++;
            if (array[j] > array[j + 1]) {
                troca(&array[j], &array[j + 1], trocas);
                trocado = 1;
            }
        }
        if (!trocado) break;
    }
}

void insertionSort(int array[], int tam, int *comparacoes, int *movimentacoes) {
    for (int i = 1; i < tam; i++) {
        int pivo = array[i];
        int j = i - 1;
        
        while (j >= 0) {
            (*comparacoes)++;
            if (array[j] > pivo) {
                array[j + 1] = array[j];
                (*movimentacoes)++;
                j--;
            } else {
                break;
            }
        }
        
        if (j + 1 != i) {
            array[j + 1] = pivo;
            (*movimentacoes)++;
        }
    }
}

void copiarArray(int origem[], int destino[], int tam) {
    for (int i = 0; i < tam; i++) {
        destino[i] = origem[i];
    }
}

int main() {
    int tam;
    scanf("%d", &tam);
    
    int *array = malloc(tam * sizeof(int));
    int *copia = malloc(tam * sizeof(int));
    
    for (int i = 0; i < tam; i++) {
        scanf("%d", &array[i]);
    }
    
    copiarArray(array, copia, tam);
    int comparacoes1 = 0, trocas1 = 0;
    selectionSort(copia, tam, &comparacoes1, &trocas1);
    printf("%d %d\n", comparacoes1, trocas1);
    
    copiarArray(array, copia, tam);
    int comparacoes2 = 0, trocas2 = 0;
    bubbleSort(copia, tam, &comparacoes2, &trocas2);
    printf("%d %d\n", comparacoes2, trocas2);
    
    copiarArray(array, copia, tam);
    int comparacoes3 = 0, movimentacoes3 = 0;
    insertionSort(copia, tam, &comparacoes3, &movimentacoes3);
    printf("%d %d\n", comparacoes3, movimentacoes3);
    
    free(array);
    free(copia);
    
    return 0;
}
